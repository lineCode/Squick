
#include "squick/base/class.h"
#include "squick/struct/protocol_define.h"

#include "world_module.h"
#include "plugin.h"
bool ProxyServerToWorldModule::Init()
{
	m_pSecurityModule = pPluginManager->FindModule<ISecurityModule>();
	m_pProxyLogicModule = pPluginManager->FindModule<IProxyLogicModule>();
	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pProxyServerNet_ServerModule = pPluginManager->FindModule<IProxyServerNet_ServerModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();
	m_pLogModule = pPluginManager->FindModule<ILogModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pNetClientModule = pPluginManager->FindModule<INetClientModule>();

    return true;
}

bool ProxyServerToWorldModule::Shut()
{
    //Final();
    //Clear();
    return true;
}

bool ProxyServerToWorldModule::Execute()
{
	ServerReport();
	return true;
}

void ProxyServerToWorldModule::OnServerInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
    Guid nPlayerID;
    SquickStruct::ServerInfoReportList xMsg;
    if (!INetModule::ReceivePB( msgID, msg, len, xMsg, nPlayerID))
    {
        return;
    }

    for (int i = 0; i < xMsg.server_list_size(); ++i)
    {
        const SquickStruct::ServerInfoReport& xData = xMsg.server_list(i);

        //type
        ConnectData xServerData;

        xServerData.nGameID = xData.server_id();
        xServerData.ip = xData.server_ip();
        xServerData.nPort = xData.server_port();
        xServerData.name = xData.server_name();
		xServerData.nWorkLoad = xData.server_cur_count();
        xServerData.eServerType = (SQUICK_SERVER_TYPES)xData.server_type();

        switch (xServerData.eServerType)
        {
            case SQUICK_SERVER_TYPES::SQUICK_ST_GAME:
            {
                m_pNetClientModule->AddServer(xServerData);
            }
            break;
            case SQUICK_SERVER_TYPES::SQUICK_ST_WORLD:
            {
				m_pNetClientModule->AddServer(xServerData);
            }
            break;
            default:
                break;
        }

    }
}

void ProxyServerToWorldModule::OnSocketWSEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet)
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

void ProxyServerToWorldModule::Register(INet* pNet)
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
            if (serverType == SQUICK_SERVER_TYPES::SQUICK_ST_PROXY && pPluginManager->GetAppID() == serverID)
            {
                const int nPort = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Port());
                const int maxConnect = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::MaxOnline());
                //const int nCpus = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::CpuCount());
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

                SQUICK_SHARE_PTR<ConnectData> pServerData = GetClusterModule()->GetServerNetInfo(pNet);
                if (pServerData)
                {
                    int nTargetID = pServerData->nGameID;
					GetClusterModule()->SendToServerByPB(nTargetID, SquickStruct::EGameMsgID::PTWG_PROXY_REGISTERED, xMsg);

                    m_pLogModule->LogInfo(Guid(0, pData->server_id()), pData->server_name(), "Register");
                }
            }
        }
    }
}

void ProxyServerToWorldModule::ServerReport()
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
			if ( pPluginManager->GetAppID() == serverID)
			{
				const int nPort = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Port());
				const int maxConnect = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::MaxOnline());
				const std::string& name = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::ID());
				const std::string& ip = m_pElementModule->GetPropertyString(strId, SquickProtocol::Server::IP());

				SquickStruct::ServerInfoReport reqMsg;

				reqMsg.set_server_id(serverID);
				reqMsg.set_server_name(strId);
                ////////cur count
				reqMsg.set_server_cur_count(0);
				reqMsg.set_server_ip(ip);
				reqMsg.set_server_port(nPort);
				reqMsg.set_server_max_online(maxConnect);
				reqMsg.set_server_state(SquickStruct::EST_NARMAL);
				reqMsg.set_server_type(serverType);


				m_pNetClientModule->SendToAllServerByPB(SQUICK_SERVER_TYPES::SQUICK_ST_WORLD, SquickStruct::STS_SERVER_REPORT, reqMsg, Guid());
		
			}
		}
	}
}

bool ProxyServerToWorldModule::AfterInit()
{
	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_WORLD, SquickStruct::ACK_CONNECT_WORLD, this, &ProxyServerToWorldModule::OnSelectServerResultProcess);
	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_WORLD, SquickStruct::STS_NET_INFO, this, &ProxyServerToWorldModule::OnServerInfoProcess);
	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_WORLD, this, &ProxyServerToWorldModule::OnOtherMessage);

	m_pNetClientModule->AddEventCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_WORLD, this, &ProxyServerToWorldModule::OnSocketWSEvent);
	m_pNetClientModule->ExpandBufferSize();

    SQUICK_SHARE_PTR<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Server::ThisName());
    if (xLogicClass)
    {
		const std::vector<std::string>& strIdList = xLogicClass->GetIDList(); 
		
		const int nCurAppID = pPluginManager->GetAppID();
		std::vector<std::string>::const_iterator itr =
			std::find_if(strIdList.begin(), strIdList.end(), [&](const std::string& strConfigId)
		{
			return nCurAppID == m_pElementModule->GetPropertyInt32(strConfigId, SquickProtocol::Server::ServerID());
		});

		if (strIdList.end() == itr)
		{
			std::ostringstream strLog;
			strLog << "Cannot find current server, AppID = " << nCurAppID;
			m_pLogModule->LogError(NULL_OBJECT, strLog, __FILE__, __LINE__);
			NFASSERT(-1, "Cannot find current server", __FILE__, __FUNCTION__);
			exit(0);
		}

		const int nCurArea = m_pElementModule->GetPropertyInt32(*itr, SquickProtocol::Server::Area());

		for (int i = 0; i < strIdList.size(); ++i)
		{
			const std::string& strId = strIdList[i];

            const int serverType = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Type());
            const int serverID = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::ServerID());
			const int nServerArea = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Area());
			if (serverType == SQUICK_SERVER_TYPES::SQUICK_ST_WORLD && nCurArea == nServerArea)
            {
                const int nPort = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Port());
                //const int maxConnect = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::MaxOnline());
                //const int nCpus = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::CpuCount());
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


void ProxyServerToWorldModule::OnSelectServerResultProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
    
    Guid nPlayerID;
    SquickStruct::AckConnectWorldResult xMsg;
    if (!INetModule::ReceivePB( msgID, msg, len, xMsg, nPlayerID))
    {
        return;
    }

    SQUICK_SHARE_PTR<ClientConnectData> pConnectData = mWantToConnectMap.GetElement(xMsg.account());
    if (NULL != pConnectData)
    {
        pConnectData->strConnectKey = xMsg.world_key();
        return;
    }

    pConnectData = SQUICK_SHARE_PTR<ClientConnectData>(SQUICK_NEW ClientConnectData());
    pConnectData->account = xMsg.account();
    pConnectData->strConnectKey = xMsg.world_key();
    mWantToConnectMap.AddElement(pConnectData->account, pConnectData);
}

INetClientModule* ProxyServerToWorldModule::GetClusterModule()
{
	return m_pNetClientModule;
}

bool ProxyServerToWorldModule::VerifyConnectData(const std::string& account, const std::string& strKey)
{
    SQUICK_SHARE_PTR<ClientConnectData> pConnectData = mWantToConnectMap.GetElement(account);
    if (pConnectData && strKey == pConnectData->strConnectKey)
    {
        mWantToConnectMap.RemoveElement(account);

        return true;
    }

    return false;
}

void ProxyServerToWorldModule::LogServerInfo(const std::string& strServerInfo)
{
    m_pLogModule->LogInfo(Guid(), strServerInfo, "");
}

void ProxyServerToWorldModule::OnOtherMessage(const NFSOCK sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	m_pProxyServerNet_ServerModule->Transport(sockIndex, msgID, msg, len);
}
