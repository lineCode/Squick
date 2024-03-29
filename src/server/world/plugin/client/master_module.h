
#ifndef SQUICK_WORLDNET_CLIENT_MODULE_H
#define SQUICK_WORLDNET_CLIENT_MODULE_H

#include "squick/struct/struct.h"

//#include "../server/world_logic.h"
#include "squick/base/net.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/log.h"
#include "squick/base/net_client.h"
#include "squick/base/security.h"

#include "../server/if_server_module.h"
#include "if_master_module.h"


class WorldToMasterModule
	: public IWorldToMasterModule
{
public:
	WorldToMasterModule(IPluginManager* p)
	{
		pPluginManager = p;
		mLastReportTime = 0;
        m_bIsExecute = true;
	}

	virtual bool Init();
	virtual bool BeforeShut();
	virtual bool Shut();
	virtual bool Execute();
	virtual bool AfterInit();

protected:

	void OnSocketMSEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);
	
	void OnClientDisconnect(const NFSOCK nAddress);
	
	void OnClientConnected(const NFSOCK nAddress);

	virtual void LogServerInfo(const std::string& strServerInfo);


	void Register(INet* pNet);
	void ServerReport();
	void RefreshWorldInfo();
	void OnServerInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

	void OnSelectServerProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnKickClientProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

	void InvalidMessage(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
private:
	INT64 mLastReportTime;

	ILogModule* m_pLogModule;
	IElementModule* m_pElementModule;
	IClassModule* m_pClassModule;
	IWorldNet_ServerModule* m_pWorldNet_ServerModule;
	INetClientModule* m_pNetClientModule;
	INetModule* m_pNetModule;
	ISecurityModule* m_pSecurityModule;
};

#endif