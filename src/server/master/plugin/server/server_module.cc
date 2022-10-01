
#include "plugin.h"
#include "squick/struct/protocol_define.h"
#include "server_module.h"

MasterNet_ServerModule::~MasterNet_ServerModule()
{

}

bool MasterNet_ServerModule::Init()
{
	this->pPluginManager->SetAppType(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER);

	m_pNetModule = pPluginManager->FindModule<INetModule>();
	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pLogModule = pPluginManager->FindModule<ILogModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();

	return true;
}

bool MasterNet_ServerModule::Shut()
{
	return true;
}

void MasterNet_ServerModule::OnWorldRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ServerInfoReportList xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const SquickStruct::ServerInfoReport& xData = xMsg.server_list(i);
		SQUICK_SHARE_PTR<ServerData> pServerData = mWorldMap.GetElement(xData.server_id());
		if (!pServerData)
		{
			pServerData = SQUICK_SHARE_PTR<ServerData>(SQUICK_NEW ServerData());
			mWorldMap.AddElement(xData.server_id(), pServerData);
		}

		pServerData->nFD = sockIndex;
		*(pServerData->pData) = xData;

		m_pLogModule->LogInfo(Guid(0, xData.server_id()), xData.server_name(), "WorldRegistered");
	}


	SynWorldToLoginAndWorld();
}

void MasterNet_ServerModule::OnWorldUnRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ServerInfoReportList xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const SquickStruct::ServerInfoReport& xData = xMsg.server_list(i);
		mWorldMap.RemoveElement(xData.server_id());


		m_pLogModule->LogInfo(Guid(0, xData.server_id()), xData.server_name(), "WorldUnRegistered");
	}

	SynWorldToLoginAndWorld();
}

void MasterNet_ServerModule::OnRefreshWorldInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ServerInfoReportList xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const SquickStruct::ServerInfoReport& xData = xMsg.server_list(i);
		SQUICK_SHARE_PTR<ServerData> pServerData = mWorldMap.GetElement(xData.server_id());
		if (!pServerData)
		{
			pServerData = SQUICK_SHARE_PTR<ServerData>(SQUICK_NEW ServerData());
			mWorldMap.AddElement(xData.server_id(), pServerData);
		}

		pServerData->nFD = sockIndex;
		*(pServerData->pData) = xData;

		m_pLogModule->LogInfo(Guid(0, xData.server_id()), xData.server_name(), "RefreshWorldInfo");

	}

	SynWorldToLoginAndWorld();
}

void MasterNet_ServerModule::OnLoginRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ServerInfoReportList xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const SquickStruct::ServerInfoReport& xData = xMsg.server_list(i);
		SQUICK_SHARE_PTR<ServerData> pServerData = mLoginMap.GetElement(xData.server_id());
		if (!pServerData)
		{
			pServerData = SQUICK_SHARE_PTR<ServerData>(SQUICK_NEW ServerData());
			mLoginMap.AddElement(xData.server_id(), pServerData);
		}

		pServerData->nFD = sockIndex;
		*(pServerData->pData) = xData;

		m_pLogModule->LogInfo(Guid(0, xData.server_id()), xData.server_name(), "LoginRegistered");
	}

	SynWorldToLoginAndWorld();
}

void MasterNet_ServerModule::OnLoginUnRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ServerInfoReportList xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const SquickStruct::ServerInfoReport& xData = xMsg.server_list(i);

		mLoginMap.RemoveElement(xData.server_id());

		m_pLogModule->LogInfo(Guid(0, xData.server_id()), xData.server_name(), "LoginUnRegistered");

	}
}

void MasterNet_ServerModule::OnRefreshLoginInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ServerInfoReportList xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const SquickStruct::ServerInfoReport& xData = xMsg.server_list(i);
		SQUICK_SHARE_PTR<ServerData> pServerData = mLoginMap.GetElement(xData.server_id());
		if (!pServerData)
		{
			pServerData = SQUICK_SHARE_PTR<ServerData>(SQUICK_NEW ServerData());
			mLoginMap.AddElement(xData.server_id(), pServerData);
		}

		pServerData->nFD = sockIndex;
		*(pServerData->pData) = xData;

		m_pLogModule->LogInfo(Guid(0, xData.server_id()), xData.server_name(), "RefreshLoginInfo");

	}
}

void MasterNet_ServerModule::OnSelectWorldProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ReqConnectWorld xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	SQUICK_SHARE_PTR<ServerData> pServerData = mWorldMap.GetElement(xMsg.world_id());
	if (!pServerData)
	{
		return;
	}

	m_pNetModule->SendMsgPB(SquickStruct::EGameMsgID::REQ_CONNECT_WORLD, xMsg, pServerData->nFD);
}

bool MasterNet_ServerModule::Execute()
{
	LogGameServer();

	return true;
}

void MasterNet_ServerModule::OnSelectServerResultProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::AckConnectWorldResult xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	SQUICK_SHARE_PTR<ServerData> pServerData = mLoginMap.GetElement(xMsg.login_id());
	if (!pServerData)
	{
		return;
	}

	
	m_pNetModule->SendMsgPB(SquickStruct::EGameMsgID::ACK_CONNECT_WORLD, xMsg, pServerData->nFD);
}

bool MasterNet_ServerModule::AfterInit()
{
	m_pNetModule->AddReceiveCallBack(SquickStruct::STS_HEART_BEAT, this, &MasterNet_ServerModule::OnHeartBeat);
	m_pNetModule->AddReceiveCallBack(SquickStruct::WTM_WORLD_REGISTERED, this, &MasterNet_ServerModule::OnWorldRegisteredProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::WTM_WORLD_UNREGISTERED, this, &MasterNet_ServerModule::OnWorldUnRegisteredProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::WTM_WORLD_REFRESH, this, &MasterNet_ServerModule::OnRefreshWorldInfoProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::LTM_LOGIN_REGISTERED, this, &MasterNet_ServerModule::OnLoginRegisteredProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::LTM_LOGIN_UNREGISTERED, this, &MasterNet_ServerModule::OnLoginUnRegisteredProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::LTM_LOGIN_REFRESH, this, &MasterNet_ServerModule::OnRefreshLoginInfoProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_CONNECT_WORLD, this, &MasterNet_ServerModule::OnSelectWorldProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::ACK_CONNECT_WORLD, this, &MasterNet_ServerModule::OnSelectServerResultProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::STS_SERVER_REPORT, this, &MasterNet_ServerModule::OnServerReport);

	m_pNetModule->AddReceiveCallBack(this, &MasterNet_ServerModule::InvalidMessage);

	m_pNetModule->AddEventCallBack(this, &MasterNet_ServerModule::OnSocketEvent);
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
			if (serverType == SQUICK_SERVER_TYPES::SQUICK_ST_MASTER && pPluginManager->GetAppID() == serverID)
			{
				const int nPort = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Port());
				const int maxConnect = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::MaxOnline());
				const int nCpus = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::CpuCount());
				const std::string& name = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::ID());
				const std::string& ip = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::IP());

				int nRet = m_pNetModule->Initialization(maxConnect, nPort, nCpus);
				if (nRet < 0)
				{
					std::ostringstream strLog;
					strLog << "Cannot init server net, Port = " << nPort;
					m_pLogModule->LogError(NULL_OBJECT, strLog, __FUNCTION__, __LINE__);
					NFASSERT(nRet, "Cannot init server net", __FILE__, __FUNCTION__);
					exit(0);
				}
				SquickStruct::ServerInfoReport reqMsg;

				reqMsg.set_server_id(serverID);
				reqMsg.set_server_name(strId);
				reqMsg.set_server_cur_count(0);
				reqMsg.set_server_ip(ip);
				reqMsg.set_server_port(nPort);
				reqMsg.set_server_max_online(maxConnect);
				reqMsg.set_server_state(SquickStruct::EST_NARMAL);
				reqMsg.set_server_type(serverType);

				auto pServerData = SQUICK_SHARE_PTR<ServerData>(SQUICK_NEW ServerData());
				*(pServerData->pData) = reqMsg;
				mMasterMap.AddElement(serverID, pServerData);
			}
		}
	}

	return true;
}

void MasterNet_ServerModule::OnSocketEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet)
{
	//std::cout << "OnSocketEvent::thread id=" << GetCurrentThreadId() << std::endl;

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

void MasterNet_ServerModule::OnClientDisconnect(const NFSOCK nAddress)
{
	
	SQUICK_SHARE_PTR<ServerData> pServerData = mWorldMap.First();
	while (pServerData)
	{
		if (nAddress == pServerData->nFD)
		{
			pServerData->pData->set_server_state(SquickStruct::EST_CRASH);
			pServerData->nFD = 0;

			SynWorldToLoginAndWorld();
			return;
		}

		pServerData = mWorldMap.Next();
	}

	//////////////////////////////////////////////////////////////////////////

	int serverID = 0;
	pServerData = mLoginMap.First();
	while (pServerData)
	{
		if (nAddress == pServerData->nFD)
		{
			serverID = pServerData->pData->server_id();
			break;
		}

		pServerData = mLoginMap.Next();
	}

	mLoginMap.RemoveElement(serverID);

}

void MasterNet_ServerModule::OnClientConnected(const NFSOCK nAddress)
{
}

void MasterNet_ServerModule::SynWorldToLoginAndWorld()
{
	SquickStruct::ServerInfoReportList xData;

	SQUICK_SHARE_PTR<ServerData> pServerData = mWorldMap.First();
	while (pServerData)
	{
		SquickStruct::ServerInfoReport* pData = xData.add_server_list();
		*pData = *(pServerData->pData);

		pServerData = mWorldMap.Next();
	}

	//loginserver
	pServerData = mLoginMap.First();
	while (pServerData)
	{
		m_pNetModule->SendMsgPB(SquickStruct::EGameMsgID::STS_NET_INFO, xData, pServerData->nFD);

		pServerData = mLoginMap.Next();
	}

	//world server
	pServerData = mWorldMap.First();
	while (pServerData)
	{
		SquickStruct::ServerInfoReportList xWorldData;
		const int nCurArea = m_pElementModule->GetPropertyInt(pServerData->pData->server_name(), SquickProtocol::Server::Area());

		for (int i = 0; i < xData.server_list_size(); ++i)
		{
			const SquickStruct::ServerInfoReport& xServerInfo = xData.server_list(i);
			//it must be the same area			
			const int nAreaID = m_pElementModule->GetPropertyInt(xServerInfo.server_name(), SquickProtocol::Server::Area());
			if (nAreaID == nCurArea)
			{
				SquickStruct::ServerInfoReport* pData = xWorldData.add_server_list();
				*pData = *(pServerData->pData);
			}
		}

		m_pNetModule->SendMsgPB(SquickStruct::EGameMsgID::STS_NET_INFO, xWorldData, pServerData->nFD);

		pServerData = mWorldMap.Next();
	}
	
}

void MasterNet_ServerModule::LogGameServer()
{
	if (mnLastLogTime + 60 > GetPluginManager()->GetNowTime())
	{
		return;
	}

	mnLastLogTime = GetPluginManager()->GetNowTime();

	//////////////////////////////////////////////////////////////////////////

	m_pLogModule->LogInfo(Guid(), "Begin Log WorldServer Info", "");

	SQUICK_SHARE_PTR<ServerData> pGameData = mWorldMap.First();
	while (pGameData)
	{
		std::ostringstream stream;
		stream << "Type: " << pGameData->pData->server_type() << " ID: " << pGameData->pData->server_id() << " State: " << SquickStruct::EServerState_Name(pGameData->pData->server_state()) << " IP: " << pGameData->pData->server_ip() << " FD: " << pGameData->nFD;
		m_pLogModule->LogInfo(Guid(), stream);

		pGameData = mWorldMap.Next();
	}

	m_pLogModule->LogInfo(Guid(), "End Log WorldServer Info", "");

	m_pLogModule->LogInfo(Guid(), "Begin Log LoginServer Info", "");

	//////////////////////////////////////////////////////////////////////////
	pGameData = mLoginMap.First();
	while (pGameData)
	{
		std::ostringstream stream;
		stream << "Type: " << pGameData->pData->server_type() << " ID: " << pGameData->pData->server_id() << " State: " << SquickStruct::EServerState_Name(pGameData->pData->server_state()) << " IP: " << pGameData->pData->server_ip() << " FD: " << pGameData->nFD;
		m_pLogModule->LogInfo(Guid(), stream);

		pGameData = mLoginMap.Next();
	}

	m_pLogModule->LogInfo(Guid(), "End Log LoginServer Info", "");

}

void MasterNet_ServerModule::OnHeartBeat(const NFSOCK sockIndex, const int msgID, const char * msg, const uint32_t len)
{
}

void MasterNet_ServerModule::InvalidMessage(const NFSOCK sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	printf("Net || umsgID=%d\n", msgID);
}

void MasterNet_ServerModule::OnServerReport(const NFSOCK nFd, const int msgId, const char* buffer, const uint32_t len)
{
	Guid xGUID;
	SquickStruct::ServerInfoReport msg;
	if (!m_pNetModule->ReceivePB(msgId, buffer, len, msg, xGUID))
	{
		return;
	}

	std::shared_ptr<ServerData> pServerData;
	switch (msg.server_type())
	{
		case SQUICK_SERVER_TYPES::SQUICK_ST_LOGIN:
		{
			pServerData = mLoginMap.GetElement(msg.server_id());
			if (!pServerData)
			{
				pServerData = std::shared_ptr<ServerData>(new ServerData());
				mLoginMap.AddElement(msg.server_id(), pServerData);
			}
		}
		break;
		case SQUICK_SERVER_TYPES::SQUICK_ST_WORLD:
		{
			pServerData = mWorldMap.GetElement(msg.server_id());
			if (!pServerData)
			{
				pServerData = std::shared_ptr<ServerData>(new ServerData());
				mWorldMap.AddElement(msg.server_id(), pServerData);
			}
		}
		break;
		case SQUICK_SERVER_TYPES::SQUICK_ST_PROXY:
		{
			pServerData = mProxyMap.GetElement(msg.server_id());
			if (!pServerData)
			{
				pServerData = std::shared_ptr<ServerData>(new ServerData());
				mProxyMap.AddElement(msg.server_id(), pServerData);
			}
		}
		break;
		case SQUICK_SERVER_TYPES::SQUICK_ST_GAME:
		{
			pServerData = mGameMap.GetElement(msg.server_id());
			if (!pServerData)
			{
				pServerData = std::shared_ptr<ServerData>(new ServerData());
				mGameMap.AddElement(msg.server_id(), pServerData);
			}
		}
		break;

		default:
		{
			//m_pLogModule->LogError("UNKNOW SERVER TYPE", msg.server_type());
		}
		break;
	}

	//udate status
	if (pServerData)
	{
		pServerData->nFD = nFd;
		*(pServerData->pData) = msg;
	}
}

std::string MasterNet_ServerModule::GetServersStatus()
{
	/*
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	rapidjson::Value root(rapidjson::kObjectType);

	root.AddMember("code", 0, allocator);
	root.AddMember("errMsg", "", allocator);
	root.AddMember("nowTime", pPluginManager->GetNowTime(), allocator);

	rapidjson::Value master(rapidjson::kArrayType);
	std::shared_ptr<ServerData> pServerData = mMasterMap.First();
	while (pServerData)
	{
		rapidjson::Value server(rapidjson::kObjectType);
		server.AddMember("serverId", pServerData->pData->server_id(), allocator);
		server.AddMember("servrName", rapidjson::Value(pServerData->pData->server_name().c_str(), allocator), allocator);
		server.AddMember("ip", rapidjson::Value(pServerData->pData->server_ip().c_str(), allocator), allocator);
		server.AddMember("port", pServerData->pData->server_port(), allocator);
		server.AddMember("onlineCount", pServerData->pData->server_cur_count(), allocator);
		server.AddMember("status", (int)pServerData->pData->server_state(), allocator);
		
		master.PushBack(server, allocator);
		pServerData = mMasterMap.Next();
	}
	root.AddMember("master", master, allocator);

	rapidjson::Value logins(rapidjson::kArrayType);
	pServerData = mLoginMap.First();
	while (pServerData)
	{
		rapidjson::Value server(rapidjson::kObjectType);
		server.AddMember("serverId", pServerData->pData->server_id(), allocator);
		server.AddMember("servrName", rapidjson::Value(pServerData->pData->server_name().c_str(), allocator), allocator);
		server.AddMember("ip", rapidjson::Value(pServerData->pData->server_ip().c_str(), allocator), allocator);
		server.AddMember("port", pServerData->pData->server_port(), allocator);
		server.AddMember("onlineCount", pServerData->pData->server_cur_count(), allocator);
		server.AddMember("status", (int)pServerData->pData->server_state(), allocator);
		
		logins.PushBack(server, allocator);
		pServerData = mLoginMap.Next();
	}
	root.AddMember("logins", logins, allocator);

	rapidjson::Value worlds(rapidjson::kArrayType);
	pServerData = mWorldMap.First();
	while (pServerData.get())
	{
		rapidjson::Value server(rapidjson::kObjectType);
		server.AddMember("serverId", pServerData->pData->server_id(), allocator);
		server.AddMember("servrName", rapidjson::Value(pServerData->pData->server_name().c_str(), allocator), allocator);
		server.AddMember("ip", rapidjson::Value(pServerData->pData->server_ip().c_str(), allocator), allocator);
		server.AddMember("port", pServerData->pData->server_port(), allocator);
		server.AddMember("onlineCount", pServerData->pData->server_cur_count(), allocator);
		server.AddMember("status", (int)pServerData->pData->server_state(), allocator);
		
		worlds.PushBack(server, allocator);
		pServerData = mWorldMap.Next();
	}
	root.AddMember("worlds", worlds, allocator);

	rapidjson::Value proxys(rapidjson::kArrayType);
	pServerData = mProxyMap.First();
	while (pServerData.get())
	{
		rapidjson::Value server(rapidjson::kObjectType);
		server.AddMember("serverId", pServerData->pData->server_id(), allocator);
		server.AddMember("servrName", rapidjson::Value(pServerData->pData->server_name().c_str(), allocator), allocator);
		server.AddMember("ip", rapidjson::Value(pServerData->pData->server_ip().c_str(), allocator), allocator);
		server.AddMember("port", pServerData->pData->server_port(), allocator);
		server.AddMember("onlineCount", pServerData->pData->server_cur_count(), allocator);
		server.AddMember("status", (int)pServerData->pData->server_state(), allocator);

		proxys.PushBack(server, allocator);
		pServerData = mProxyMap.Next();
	}
	root.AddMember("proxys", proxys, allocator);

	rapidjson::Value games(rapidjson::kArrayType);
	pServerData = mGameMap.First();
	while (pServerData.get())
	{
		rapidjson::Value server(rapidjson::kObjectType);
		server.AddMember("serverId", pServerData->pData->server_id(), allocator);
		server.AddMember("servrName", rapidjson::Value(pServerData->pData->server_name().c_str(), allocator), allocator);
		server.AddMember("ip", rapidjson::Value(pServerData->pData->server_ip().c_str(), allocator), allocator);
		server.AddMember("port", pServerData->pData->server_port(), allocator);
		server.AddMember("onlineCount", pServerData->pData->server_cur_count(), allocator);
		server.AddMember("status", (int)pServerData->pData->server_state(), allocator);
		
		games.PushBack(server, allocator);
		pServerData = mGameMap.Next();
	}
	root.AddMember("games", games, allocator);

	rapidjson::StringBuffer jsonBuf;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuf);
	root.Accept(jsonWriter);

	return jsonBuf.GetString();

	*/
	return "";
}
