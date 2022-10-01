

#ifndef SQUICK_MASTERNET_SERVER_MODULE_H
#define SQUICK_MASTERNET_SERVER_MODULE_H

#include "squick/struct/struct.h"
#include "squick/base/kernel.h"
#include "squick/base/log.h"
#include "squick/base/net.h"
#include "squick/base/class.h"
#include "squick/base/element.h"

#include "if_server_module.h"

class MasterNet_ServerModule
    : public IMasterNet_ServerModule
{
public:
    MasterNet_ServerModule(IPluginManager* p)
    {
        m_bIsExecute = true;
		pPluginManager = p;
        mnLastLogTime = pPluginManager->GetNowTime();
    }
	virtual ~MasterNet_ServerModule();

    virtual bool Init();
    virtual bool Shut();

    virtual bool AfterInit();
    virtual bool Execute();

    virtual void LogReceive(const char* str) {}
    virtual void LogSend(const char* str) {}

	virtual std::string GetServersStatus();

protected:

    void OnSocketEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);
    void OnClientDisconnect(const NFSOCK nAddress);
    void OnClientConnected(const NFSOCK nAddress);

protected:
    void OnWorldRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnWorldUnRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnRefreshWorldInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

    //////////////////////////////////////////////////////////////////////////
    void OnLoginRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnLoginUnRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnRefreshLoginInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

    void OnSelectWorldProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnSelectServerResultProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

	void OnServerReport(const NFSOCK nFd, const int msgId, const char* buffer, const uint32_t len);

    //////////////////////////////////////////////////////////////////////////

    void SynWorldToLoginAndWorld();
    void LogGameServer();

	void OnHeartBeat(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void InvalidMessage(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

private:

    INT64 mnLastLogTime;

    //serverid,data
	MapEx<int, ServerData> mMasterMap;
	MapEx<int, ServerData> mLoginMap;
    MapEx<int, ServerData> mWorldMap;
	MapEx<int, ServerData> mProxyMap;
	MapEx<int, ServerData> mGameMap;


    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
    IKernelModule* m_pKernelModule;
    ILogModule* m_pLogModule;
	INetModule* m_pNetModule;
};

#endif