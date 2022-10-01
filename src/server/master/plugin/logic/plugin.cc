

#include "master_module.h"
#include "plugin.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, MasterServerPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, MasterServerPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int MasterServerPlugin::GetPluginVersion()
{
    return 0;
}

const std::string MasterServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(MasterServerPlugin);
}

void MasterServerPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, IMasterModule, MasterModule)


}

void MasterServerPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IMasterModule, MasterModule)
}
