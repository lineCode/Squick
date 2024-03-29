

#include "plugin.h"
#include "server_module.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, LoginNet_ServerPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, LoginNet_ServerPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int LoginNet_ServerPlugin::GetPluginVersion()
{
    return 0;
}

const std::string LoginNet_ServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(LoginNet_ServerPlugin);
}

void LoginNet_ServerPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, ILoginNet_ServerModule, LILoginNet_ServerModule)
}

void LoginNet_ServerPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, ILoginNet_ServerModule, LILoginNet_ServerModule)
}