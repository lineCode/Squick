

#ifndef SQUICK_GAMESERVERPLUGIN_H
#define SQUICK_GAMESERVERPLUGIN_H

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class GameServerPlugin : public IPlugin
{
public:
    GameServerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};

#endif
