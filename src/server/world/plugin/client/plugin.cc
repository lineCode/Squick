
#include "plugin.h"
#include "master_module.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, WorldNet_ClientPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, WorldNet_ClientPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int WorldNet_ClientPlugin::GetPluginVersion()
{
    return 0;
}

const std::string WorldNet_ClientPlugin::GetPluginName()
{
	return GET_CLASS_NAME(WorldNet_ClientPlugin);
}

void WorldNet_ClientPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, IWorldToMasterModule, WorldToMasterModule)
}

void WorldNet_ClientPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IWorldToMasterModule, WorldToMasterModule)
}