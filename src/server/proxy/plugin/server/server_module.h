
#ifndef SQUICK_PROXYSERVER_SERVER_MODULE_H
#define SQUICK_PROXYSERVER_SERVER_MODULE_H

#include "squick/core/consistent_hash.h"
#include "squick/struct/struct.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"
#include "squick/base/log.h"
#include "squick/base/net.h"
#include "squick/base/element.h"
#include "squick/base/net_client.h"
#include "squick/base/security.h"
#include "squick/base/ws.h"
#include "squick/base/thread_pool.h"

#include "../client/if_game_module.h"
#include "../client/if_world_module.h"
#include "if_server_module.h"


class ProxyServerNet_ServerModule : public IProxyServerNet_ServerModule
{
public:
    ProxyServerNet_ServerModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();

    virtual int Transport(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

    
    virtual int EnterGameSuccessEvent(const Guid xClientID, const Guid xPlayerID);

protected:

    void OnSocketClientEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

    void OnClientDisconnect(const NFSOCK nAddress);
    void OnClientConnected(const NFSOCK nAddress);

    void OnConnectKeyProcessWS(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnConnectKeyProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnReqServerListProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnSelectServerProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnReqRoleListProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnReqCreateRoleProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnReqDelRoleProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnReqEnterGameServer(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

    //////////////////////////////////////////////////////////////////////////

	void OnOtherMessage(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
protected:

    MapEx<Guid, NFSOCK> mxClientIdent;
protected:
    INetClientModule* m_pNetClientModule;
    IKernelModule* m_pKernelModule;
    ILogModule* m_pLogModule;
    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
	INetModule* m_pNetModule;
    IWSModule* m_pWsModule;
	ISecurityModule* m_pSecurityModule;
	IProxyServerToWorldModule* m_pProxyToWorldModule;
    IThreadPoolModule* m_pThreadPoolModule;
};

#endif