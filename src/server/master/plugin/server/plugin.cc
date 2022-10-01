
#include "plugin.h"
#include "server_module.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, MasterNet_ServerPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, MasterNet_ServerPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int MasterNet_ServerPlugin::GetPluginVersion()
{
    return 0;
}

const std::string MasterNet_ServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(MasterNet_ServerPlugin);
}

void MasterNet_ServerPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, IMasterNet_ServerModule, MasterNet_ServerModule)
}

void MasterNet_ServerPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IMasterNet_ServerModule, MasterNet_ServerModule)
}