


#include "inventory_plugin.h"
#include "inventory_module.h"

#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, InventoryPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, InventoryPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int InventoryPlugin::GetPluginVersion()
{
    return 0;
}

const std::string InventoryPlugin::GetPluginName()
{
	return GET_CLASS_NAME(InventoryPlugin);
}

void InventoryPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, IInventoryModule, InventoryModule)
}

void InventoryPlugin::Uninstall()
{

	UNREGISTER_MODULE(pPluginManager, IInventoryModule, InventoryModule)
}