

#ifndef SQUICK_CONSUME_MANAGER_PLUGIN_H
#define SQUICK_CONSUME_MANAGER_PLUGIN_H

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class ConsumeManagerPlugin : public IPlugin
{
public:
	ConsumeManagerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif