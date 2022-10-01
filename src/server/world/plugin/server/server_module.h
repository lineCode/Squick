
#ifndef SQUICK_WORLDNET_SERVER_MODULE_H
#define SQUICK_WORLDNET_SERVER_MODULE_H

#include "squick/core/map.h"
#include "squick/struct/struct.h"
#include "squick/base/thread_pool.h"
#include "squick/base/net.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"
//#include "squick/base/login_net_server.h"
#include "../client/if_master_module.h"
//#include "world_logic.h"
#include "if_server_module.h"

class WorldNet_ServerModule
    : public IWorldNet_ServerModule
{
public:
    WorldNet_ServerModule(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
        mnLastCheckTime = pPluginManager->GetNowTime();
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();
	virtual void OnServerInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

	virtual bool IsPrimaryWorldServer();
	virtual int GetWorldAreaID();

	virtual bool SendMsgToGame(const int gameID, const int msgID, const std::string& xData);
	virtual bool SendMsgToGame(const int gameID, const int msgID, const google::protobuf::Message& xData);

    virtual bool SendMsgToGamePlayer(const Guid nPlayer, const int msgID, const std::string& xData);
    virtual bool SendMsgToGamePlayer(const Guid nPlayer, const int msgID, const google::protobuf::Message& xData);
    virtual bool SendMsgToGamePlayer(const DataList& argObjectVar, const int msgID, google::protobuf::Message& xData);

    virtual SQUICK_SHARE_PTR<ServerData> GetSuitProxyToEnter();
	virtual SQUICK_SHARE_PTR<ServerData> GetSuitGameToEnter(const int arg);

    virtual int GetPlayerGameID(const Guid self);
    virtual const std::vector<Guid>& GetOnlinePlayers();

    virtual SQUICK_SHARE_PTR<IWorldNet_ServerModule::PlayerData> GetPlayerData(const Guid& id);

protected:
	virtual bool AddOnLineReceiveCallBack(std::shared_ptr<std::function<void(const Guid)>> cb);
	virtual bool AddOffLineReceiveCallBack(std::shared_ptr<std::function<void(const Guid)>> cb);
protected:

    void OnSocketEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

    void OnClientDisconnect(const NFSOCK nAddress);
    void OnClientConnected(const NFSOCK nAddress);


    void OnOnlineProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnOfflineProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

    void OnTransmitServerReport(const NFSOCK nFd, const int msgId, const char *buffer, const uint32_t len);
    void ServerReport(int reportServerId, SquickStruct::EServerState serverStatus);

protected:

    void OnGameServerRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnGameServerUnRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnRefreshGameServerInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

    void OnProxyServerRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnProxyServerUnRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnRefreshProxyServerInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

	void OnDBServerRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnDBServerUnRegisteredProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnRefreshDBServerInfoProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

	void SynGameToProxy();
    void SynGameToProxy(const NFSOCK nFD);

	void SynWorldToProxy();
	void SynWorldToProxy(const NFSOCK nFD);

	void SynWorldToGame();
	void SynWorldToGame(const NFSOCK nFD);

	void SynWorldToDB();
	void SynWorldToDB(const NFSOCK nFD);

	void SynDBToGame();
	void SynDBToGame(const NFSOCK nFD);

    void LogGameServer();

private:
	int mAreaID = 0;

	std::vector<std::shared_ptr<std::function<void(const Guid)>>> mPlayerOnLineCallBackFunc;
	std::vector<std::shared_ptr<std::function<void(const Guid)>>> mPlayerOffLineCallBackFunc;

	MapEx<Guid, PlayerData> mPlayersData;
    INT64 mnLastCheckTime;

    //serverid,data
	NFConsistentHashMapEx<int, ServerData> mWorldMap;
	NFConsistentHashMapEx<int, ServerData> mGameMap;
	NFConsistentHashMapEx<int, ServerData> mProxyMap;
	NFConsistentHashMapEx<int, ServerData> mDBMap;

    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
    IKernelModule* m_pKernelModule;
    ILogModule* m_pLogModule;
	INetModule* m_pNetModule;
	INetClientModule* m_pNetClientModule;
    IThreadPoolModule* m_pThreadPoolModule;
};

#endif
