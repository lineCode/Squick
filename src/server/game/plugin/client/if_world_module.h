
#ifndef SQUICK_INTF_GAME_SERVER_TO_WORLD_MODULE_H
#define SQUICK_INTF_GAME_SERVER_TO_WORLD_MODULE_H

#include <iostream>
#include <squick/base/module.h>
#include <squick/base/net_client.h>

class IGameServerToWorldModule
	: public IModule
{
public:
	virtual void TransmitToWorld(const int nHashKey, const int msgID, const google::protobuf::Message& xData) = 0;
	virtual void SendOnline(const Guid& self) = 0;
	virtual void SendOffline(const Guid& self) = 0;
};

#endif