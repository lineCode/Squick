


#ifndef SQUICK_INVENTORY_PLUGIN_H
#define SQUICK_INVENTORY_PLUGIN_H

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class InventoryPlugin : public IPlugin
{
public:
	InventoryPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif