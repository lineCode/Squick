

#ifndef SQUICK_GAMESERVER_NETCLIENTPLUGIN_MODULE_H
#define SQUICK_GAMESERVER_NETCLIENTPLUGIN_MODULE_H
///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFGAMESERVERNET_CLIENTPLUGIN_EXPORTS
#define NFGAMESERVERNET_CLIENTPLUGIN_API __declspec(dllexport)
#else
#define NFGAMESERVERNET_CLIENTPLUGIN_API __declspec(dllimport)
#endif

class GameServerNet_ClientPlugin : public IPlugin
{
public:
    GameServerNet_ClientPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};

#endif