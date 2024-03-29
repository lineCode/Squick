#pragma once

#include <squick/base/module.h>
#include <squick/base/net.h>

class IGameServerNet_ServerModule
    : public IModule
{
public:

    struct GateBaseInfo
    {
		enum ERoleStatus
		{
			E_LOADING = 1,
			E_LOADED = 2,
		};

        GateBaseInfo()
        {
            nActorID = 0;
            gateID = 0;
			eStatus = E_LOADING;
        }

        GateBaseInfo(const int gateID, const Guid xIdent)
        {
            this->nActorID = 0;
			this->gateID = gateID;
			this->xClientID = xIdent;
        }

        int nActorID;
		int gateID;
		ERoleStatus eStatus;
        Guid xClientID;
    };

    struct GateServerInfo
    {
        ServerData xServerData;

        std::map<Guid, NFSOCK> xRoleInfo;
    };

public:

    //virtual void SendMsgPBToGate(const uint16_t msgID, const std::string& xMsg, const Guid& self) = 0;
    virtual void SendMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const Guid& self) = 0;
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const int sceneID, const int groupID) = 0;
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const int sceneID, const int groupID, const Guid exceptID) = 0;

	virtual void SendMsgToGate(const uint16_t msgID, const std::string& msg, const Guid& self) = 0;
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, const std::string& msg, const int sceneID, const int groupID) = 0;
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, const std::string& msg, const int sceneID, const int groupID, const Guid exceptID) = 0;


    virtual bool AddPlayerGateInfo(const Guid& roleID, const Guid& clientID, const int gateID) = 0;
    virtual bool RemovePlayerGateInfo(const Guid& roleID) = 0;

    virtual SQUICK_SHARE_PTR<GateBaseInfo> GetPlayerGateInfo(const Guid& roleID) = 0;
	virtual SQUICK_SHARE_PTR<GateServerInfo> GetGateServerInfo(const int gateID) = 0;
	virtual SQUICK_SHARE_PTR<GateServerInfo> GetGateServerInfoBySockIndex(const NFSOCK sockIndex) = 0;
};
