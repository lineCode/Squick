

#ifndef SQUICK_GAMESERVERNET_SERVERPLUGIN_H
#define SQUICK_GAMESERVERNET_SERVERPLUGIN_H

///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFGAMESERVERNET_SERVERPLUGIN_EXPORTS
#define NFGAMESERVERNET_SERVERPLUGIN_API __declspec(dllexport)
#else
#define NFGAMESERVERNET_SERVERPLUGIN_API __declspec(dllimport)
#endif

class GameServerNet_ServerPlugin : public IPlugin
{
public:
    GameServerNet_ServerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif