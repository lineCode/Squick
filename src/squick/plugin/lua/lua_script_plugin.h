

#ifndef SQUICK_LUA_SCRIPT_PLUGIN_H
#define SQUICK_LUA_SCRIPT_PLUGIN_H

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class LuaScriptPlugin : public IPlugin
{
public:
    LuaScriptPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif