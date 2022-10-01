

#ifndef SQUICK_GAMESERVER_MODULE_H
#define SQUICK_GAMESERVER_MODULE_H

#include "squick/core/map.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"
#include "./if_game_server_module.h"
class GameServerModule
    : public IGameServerModule
{
public:
    GameServerModule(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
    }
    virtual ~GameServerModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();
    virtual bool BeforeShut();


protected:


protected:
    IClassModule* m_pClassModule;
    IKernelModule* m_pKernelModule;
private:
};

#endif
