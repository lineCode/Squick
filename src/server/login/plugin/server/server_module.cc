
#include "plugin.h"
#include "server_module.h"
#include "squick/struct/protocol_define.h"

bool LILoginNet_ServerModule::Init()
{
	this->pPluginManager->SetAppType(SQUICK_SERVER_TYPES::SQUICK_ST_LOGIN);

	m_pNetModule = pPluginManager->FindModule<INetModule>();
	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pLogModule = pPluginManager->FindModule<ILogModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();
	m_pNetClientModule = pPluginManager->FindModule<INetClientModule>();
	m_pLoginToMasterModule = pPluginManager->FindModule<ILoginToMasterModule>();
	m_pThreadPoolModule = pPluginManager->FindModule<IThreadPoolModule>();

	return true;
}

bool LILoginNet_ServerModule::Shut()
{
	return true;
}

bool LILoginNet_ServerModule::BeforeShut()
{
	return true;
}

bool LILoginNet_ServerModule::AfterInit()
{
	m_pNetModule->AddReceiveCallBack(SquickStruct::STS_HEART_BEAT, this, &LILoginNet_ServerModule::OnHeartBeat);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_LOGIN, this, &LILoginNet_ServerModule::OnLoginProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_LOGOUT, this, &LILoginNet_ServerModule::OnLogOut);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_CONNECT_WORLD, this, &LILoginNet_ServerModule::OnSelectWorldProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_WORLD_LIST, this, &LILoginNet_ServerModule::OnViewWorldProcess);
	m_pNetModule->AddReceiveCallBack(this, &LILoginNet_ServerModule::InvalidMessage);

	m_pNetModule->AddEventCallBack(this, &LILoginNet_ServerModule::OnSocketClientEvent);
	m_pNetModule->ExpandBufferSize();

	SQUICK_SHARE_PTR<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Server::ThisName());
	if (xLogicClass)
	{
		const std::vector<std::string>& strIdList = xLogicClass->GetIDList();
		for (int i = 0; i < strIdList.size(); ++i)
		{
			const std::string& strId = strIdList[i];

			const int serverType = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Type());
			const int serverID = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::ServerID());
			if (serverType == SQUICK_SERVER_TYPES::SQUICK_ST_LOGIN && pPluginManager->GetAppID() == serverID)
			{
				const int nPort = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Port());
				const int maxConnect = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::MaxOnline());
				const int nCpus = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::CpuCount());

				int nRet = m_pNetModule->Initialization(maxConnect, nPort, nCpus);
				if (nRet < 0)
				{
					std::ostringstream strLog;
					strLog << "Cannot init server net, Port = " << nPort;
					m_pLogModule->LogError(NULL_OBJECT, strLog, __FUNCTION__, __LINE__);
					NFASSERT(nRet, "Cannot init server net", __FILE__, __FUNCTION__);
					exit(0);
				}
			}
		}
	}

	return true;
}

int LILoginNet_ServerModule::OnSelectWorldResultsProcess(const int nWorldID, const Guid xSenderID, const int nLoginID, const std::string& account, const std::string& strWorldIP, const int nWorldPort, const std::string& strWorldKey)
{
	SQUICK_SHARE_PTR<NFSOCK> xFD = mxClientIdent.GetElement(xSenderID);
	if (xFD)
	{
		SquickStruct::AckConnectWorldResult xMsg;
		xMsg.set_world_id(nWorldID);
		xMsg.mutable_sender()->CopyFrom(INetModule::StructToProtobuf(xSenderID));
		xMsg.set_login_id(nLoginID);
		xMsg.set_account(account);
		xMsg.set_world_ip(strWorldIP);
		xMsg.set_world_port(nWorldPort);
		xMsg.set_world_key(strWorldKey);

		m_pNetModule->SendMsgPB(SquickStruct::EGameMsgID::ACK_CONNECT_WORLD, xMsg, *xFD);
	}

	return 0;
}

bool LILoginNet_ServerModule::Execute()
{
	return true;
}

void LILoginNet_ServerModule::OnClientConnected(const NFSOCK nAddress)
{
	NetObject* pObject = m_pNetModule->GetNet()->GetNetObject(nAddress);
	if (pObject)
	{
		Guid xIdent = m_pKernelModule->CreateGUID();
		pObject->SetClientID(xIdent);
		mxClientIdent.AddElement(xIdent, SQUICK_SHARE_PTR<NFSOCK>(SQUICK_NEW NFSOCK(nAddress)));
	}
}

void LILoginNet_ServerModule::OnClientDisconnect(const NFSOCK nAddress)
{
	NetObject* pObject = m_pNetModule->GetNet()->GetNetObject(nAddress);
	if (pObject)
	{
		Guid xIdent = pObject->GetClientID();
		mxClientIdent.RemoveElement(xIdent);
	}
}

void LILoginNet_ServerModule::OnLoginProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ReqAccountLogin xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	NetObject* pNetObject = m_pNetModule->GetNet()->GetNetObject(sockIndex);
	if (pNetObject)
	{
		if (pNetObject->GetConnectKeyState() == 0)
		{
			std::ostringstream strLog;
			strLog << "登录, Account = " << xMsg.account() << " Password = " << xMsg.password();
			//Normally, you could check the account and password is correct or not, but for our situation, it will correct by default as here is the tutorial code.
			int loginResult = 0;//0 means successful, else means error code from account platform.
			if (0 != loginResult)
			{
				
				strLog << "Check password failed, Account = " << xMsg.account() << " Password = " << xMsg.password();
				m_pLogModule->LogError(Guid(0, sockIndex), strLog, __FUNCTION__, __LINE__);

				SquickStruct::AckEventResult xMsg;
				xMsg.set_event_code(SquickStruct::ACCOUNTPWD_INVALID);

				m_pNetModule->SendMsgPB(SquickStruct::EGameMsgID::ACK_LOGIN, xMsg, sockIndex);
				return;
			}

			pNetObject->SetConnectKeyState(1);
			pNetObject->SetAccount(xMsg.account());

			SquickStruct::AckEventResult xData;
			xData.set_event_code(SquickStruct::ACCOUNT_LOGIN_SUCCESS);

			//The login server responds the login result to the player by sock id.
			m_pNetModule->SendMsgPB(SquickStruct::EGameMsgID::ACK_LOGIN, xData, sockIndex);

			m_pLogModule->LogInfo(Guid(0, sockIndex), "Login succeeded :", xMsg.account().c_str());
		}
	}
}

void LILoginNet_ServerModule::OnSelectWorldProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ReqConnectWorld xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	NetObject* pNetObject = m_pNetModule->GetNet()->GetNetObject(sockIndex);
	if (!pNetObject)
	{
		return;
	}

	
	if (pNetObject->GetConnectKeyState() <= 0)
	{
		return;
	}

	SquickStruct::ReqConnectWorld xData;
	xData.set_world_id(xMsg.world_id());
	xData.set_login_id(pPluginManager->GetAppID());
	xData.mutable_sender()->CopyFrom(INetModule::StructToProtobuf(pNetObject->GetClientID()));
	xData.set_account(pNetObject->GetAccount());

	m_pNetClientModule->SendSuitByPB(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER, pNetObject->GetAccount(), SquickStruct::EGameMsgID::REQ_CONNECT_WORLD, xData);
}

void LILoginNet_ServerModule::OnSocketClientEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet)
{
	if (eEvent & SQUICK_NET_EVENT_EOF)
	{
		m_pLogModule->LogInfo(Guid(0, sockIndex), "SQUICK_NET_EVENT_EOF Connection closed", __FUNCTION__, __LINE__);
		OnClientDisconnect(sockIndex);
	}
	else if (eEvent & SQUICK_NET_EVENT_ERROR)
	{
		m_pLogModule->LogInfo(Guid(0, sockIndex), "SQUICK_NET_EVENT_ERROR Got an error on the connection", __FUNCTION__, __LINE__);
		OnClientDisconnect(sockIndex);
	}
	else if (eEvent & SQUICK_NET_EVENT_TIMEOUT)
	{
		m_pLogModule->LogInfo(Guid(0, sockIndex), "SQUICK_NET_EVENT_TIMEOUT read timeout", __FUNCTION__, __LINE__);
		OnClientDisconnect(sockIndex);
	}
	else  if (eEvent & SQUICK_NET_EVENT_CONNECTED)
	{
		m_pLogModule->LogInfo(Guid(0, sockIndex), "SQUICK_NET_EVENT_CONNECTED connected success", __FUNCTION__, __LINE__);
		OnClientConnected(sockIndex);
	}
}

void LILoginNet_ServerModule::SynWorldToClient(const NFSOCK nFD)
{
	SquickStruct::AckServerList xData;
	xData.set_type(SquickStruct::RSLT_WORLD_SERVER);

	MapEx<int, SquickStruct::ServerInfoReport>& xWorldMap = m_pLoginToMasterModule->GetWorldMap();
	SquickStruct::ServerInfoReport* pWorldData = xWorldMap.FirstNude();
	while (pWorldData)
	{
		SquickStruct::ServerInfo* pServerInfo = xData.add_info();

		pServerInfo->set_name(pWorldData->server_name());
		pServerInfo->set_status(pWorldData->server_state());
		pServerInfo->set_server_id(pWorldData->server_id());
		pServerInfo->set_wait_count(0);

		pWorldData = xWorldMap.NextNude();
	}


	m_pNetModule->SendMsgPB(SquickStruct::EGameMsgID::ACK_WORLD_LIST, xData, nFD);
}

void LILoginNet_ServerModule::OnViewWorldProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ReqServerList xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	if (xMsg.type() == SquickStruct::RSLT_WORLD_SERVER)
	{
		SynWorldToClient(sockIndex);
	}
}

void LILoginNet_ServerModule::OnHeartBeat(const NFSOCK sockIndex, const int msgID, const char * msg, const uint32_t len)
{
}

void LILoginNet_ServerModule::OnLogOut(const NFSOCK sockIndex, const int msgID, const char * msg, const uint32_t len)
{
}

void LILoginNet_ServerModule::InvalidMessage(const NFSOCK sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	printf("Net || umsgID=%d\n", msgID);
}
