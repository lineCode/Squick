

#include "master_module.h"
#include "plugin.h"
#include "squick/core/data_list.h"
#include "squick/struct/struct.h"
#include "squick/base/net_client.h"
#include "squick/struct/protocol_define.h"

bool WorldToMasterModule::Init()
{
	m_pNetClientModule = pPluginManager->FindModule<INetClientModule>();
	m_pNetModule = pPluginManager->FindModule<INetModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();
	m_pLogModule = pPluginManager->FindModule<ILogModule>();
	m_pWorldNet_ServerModule = pPluginManager->FindModule<IWorldNet_ServerModule>();
	m_pSecurityModule = pPluginManager->FindModule<ISecurityModule>();

	return true;
}

bool WorldToMasterModule::Shut()
{
	return true;
}

bool WorldToMasterModule::AfterInit()
{
	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER, SquickStruct::REQ_CONNECT_WORLD, this, &WorldToMasterModule::OnSelectServerProcess);
	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER, SquickStruct::REQ_KICKED_FROM_WORLD, this, &WorldToMasterModule::OnKickClientProcess);
	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER, this, &WorldToMasterModule::InvalidMessage);

	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER, SquickStruct::STS_NET_INFO, this, &WorldToMasterModule::OnServerInfoProcess);

	m_pNetClientModule->AddEventCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER, this, &WorldToMasterModule::OnSocketMSEvent);
	m_pNetClientModule->ExpandBufferSize();

	SQUICK_SHARE_PTR<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Server::ThisName());
	if (xLogicClass)
	{
		const std::vector<std::string>& strIdList = xLogicClass->GetIDList();
		for (int i = 0; i < strIdList.size(); ++i)
		{
			const std::string& strId = strIdList[i];

			const int serverType = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Type());
			const int serverID = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::ServerID());
			if (serverType == SQUICK_SERVER_TYPES::SQUICK_ST_MASTER)
			{
				const int nPort = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Port());
				const int maxConnect = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::MaxOnline());
				const int nCpus = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::CpuCount());
				const std::string& name = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::ID());
				const std::string& ip = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::IP());

				ConnectData xServerData;

				xServerData.nGameID = serverID;
				xServerData.eServerType = (SQUICK_SERVER_TYPES)serverType;
				xServerData.ip = ip;
				xServerData.nPort = nPort;
				xServerData.name = strId;

				m_pNetClientModule->AddServer(xServerData);
			}
		}
	}

	return true;
}


bool WorldToMasterModule::Execute()
{
	ServerReport();
	return true;
}

void WorldToMasterModule::Register(INet* pNet)
{
	SQUICK_SHARE_PTR<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Server::ThisName());
	if (xLogicClass)
	{
		const std::vector<std::string>& strIdList = xLogicClass->GetIDList();
		for (int i = 0; i < strIdList.size(); ++i)
		{
			const std::string& strId = strIdList[i];

			const int serverType = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Type());
			const int serverID = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::ServerID());
			if (serverType == SQUICK_SERVER_TYPES::SQUICK_ST_WORLD && pPluginManager->GetAppID() == serverID)
			{
				const int nPort = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Port());
				const int maxConnect = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::MaxOnline());
				const int nCpus = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::CpuCount());
				const std::string& name = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::ID());
				const std::string& ip = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::IP());

				SquickStruct::ServerInfoReportList xMsg;
				SquickStruct::ServerInfoReport* pData = xMsg.add_server_list();

				pData->set_server_id(serverID);
				pData->set_server_name(strId);
				pData->set_server_cur_count(0);
				pData->set_server_ip(ip);
				pData->set_server_port(nPort);
				pData->set_server_max_online(maxConnect);
				pData->set_server_state(SquickStruct::EST_NARMAL);
				pData->set_server_type(serverType);

				SQUICK_SHARE_PTR<ConnectData> pServerData = m_pNetClientModule->GetServerNetInfo(pNet);
				if (pServerData)
				{
					int nTargetID = pServerData->nGameID;
					m_pNetClientModule->SendToServerByPB(nTargetID, SquickStruct::EGameMsgID::WTM_WORLD_REGISTERED, xMsg);

					m_pLogModule->LogInfo(Guid(0, pData->server_id()), pData->server_name(), "Register");
				}
			}
		}
	}
}

void WorldToMasterModule::ServerReport()
{
	if (mLastReportTime + 10 > pPluginManager->GetNowTime())
	{
		return;
	}
	mLastReportTime = pPluginManager->GetNowTime();
	std::shared_ptr<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Server::ThisName());
	if (xLogicClass)
	{
		const std::vector<std::string>& strIdList = xLogicClass->GetIDList();
		for (int i = 0; i < strIdList.size(); ++i)
		{
			const std::string& strId = strIdList[i];

			const int serverType = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Type());
			const int serverID = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::ServerID());
			if (pPluginManager->GetAppID() == serverID)
			{
				const int nPort = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Port());
				const int maxConnect = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::MaxOnline());
				const std::string& name = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::ID());
				const std::string& ip = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::IP());

				SquickStruct::ServerInfoReport reqMsg;

				reqMsg.set_server_id(serverID);
				reqMsg.set_server_name(strId);
				reqMsg.set_server_cur_count(0);
				reqMsg.set_server_ip(ip);
				reqMsg.set_server_port(nPort);
				reqMsg.set_server_max_online(maxConnect);
				reqMsg.set_server_state(SquickStruct::EST_NARMAL);
				reqMsg.set_server_type(serverType);

				m_pNetClientModule->SendToAllServerByPB(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER, SquickStruct::STS_SERVER_REPORT, reqMsg, Guid());
			}
		}
	}
}

void WorldToMasterModule::RefreshWorldInfo()
{

}

void WorldToMasterModule::OnSelectServerProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ReqConnectWorld xMsg;
	if (!INetModule::ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	SQUICK_SHARE_PTR<ServerData> xServerData = m_pWorldNet_ServerModule->GetSuitProxyToEnter();
	if (xServerData)
	{
		const std::string& strSecurityKey = m_pSecurityModule->GetSecurityKey(xMsg.account());

		SquickStruct::AckConnectWorldResult xData;

		xData.set_world_id(xMsg.world_id());
		xData.mutable_sender()->CopyFrom(xMsg.sender());
		xData.set_login_id(xMsg.login_id());
		xData.set_account(xMsg.account());

		xData.set_world_ip(xServerData->pData->server_ip());
		xData.set_world_port(xServerData->pData->server_port());
		xData.set_world_key(strSecurityKey);

		m_pNetModule->SendMsgPB(SquickStruct::ACK_CONNECT_WORLD, xData, xServerData->nFD);

		m_pNetClientModule->SendSuitByPB(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER, xMsg.account(), SquickStruct::ACK_CONNECT_WORLD, xData);
	}

}

void WorldToMasterModule::OnKickClientProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ReqKickFromWorld xMsg;
	if (!INetModule::ReceivePB( msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	
	//     DataList var;
	//     var << xMsg.world_id() << xMsg.account();
	//     m_pEventProcessModule->DoEvent(Guid(), NFED_ON_KICK_FROM_SERVER, var);
}

void WorldToMasterModule::InvalidMessage(const NFSOCK sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	printf("Net || umsgID=%d\n", msgID);
}

void WorldToMasterModule::OnSocketMSEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet)
{
	if (eEvent & SQUICK_NET_EVENT_EOF)
	{
		m_pLogModule->LogInfo(Guid(0, sockIndex), "SQUICK_NET_EVENT_EOF Connection closed", __FUNCTION__, __LINE__);
	}
	else if (eEvent & SQUICK_NET_EVENT_ERROR)
	{
		m_pLogModule->LogInfo(Guid(0, sockIndex), "SQUICK_NET_EVENT_ERROR Got an error on the connection", __FUNCTION__, __LINE__);
	}
	else if (eEvent & SQUICK_NET_EVENT_TIMEOUT)
	{
		m_pLogModule->LogInfo(Guid(0, sockIndex), "SQUICK_NET_EVENT_TIMEOUT read timeout", __FUNCTION__, __LINE__);
	}
	else  if (eEvent & SQUICK_NET_EVENT_CONNECTED)
	{
		m_pLogModule->LogInfo(Guid(0, sockIndex), "SQUICK_NET_EVENT_CONNECTED connected success", __FUNCTION__, __LINE__);
		Register(pNet);
	}
}

void WorldToMasterModule::OnClientDisconnect(const NFSOCK nAddress)
{

}

void WorldToMasterModule::OnClientConnected(const NFSOCK nAddress)
{

}

bool WorldToMasterModule::BeforeShut()
{
	return true;
}

void WorldToMasterModule::LogServerInfo(const std::string& strServerInfo)
{
	m_pLogModule->LogInfo(Guid(), strServerInfo, "");
}

void WorldToMasterModule::OnServerInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	m_pWorldNet_ServerModule->OnServerInfoProcess(sockIndex, msgID, msg, len);
}
