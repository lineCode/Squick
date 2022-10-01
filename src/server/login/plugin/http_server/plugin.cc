

#include "plugin.h"
#include "http_server_module.h"

#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

	CREATE_PLUGIN(pm, LoginNet_HttpServerPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
	DESTROY_PLUGIN(pm, LoginNet_HttpServerPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int LoginNet_HttpServerPlugin::GetPluginVersion()
{
	return 0;
}

const std::string LoginNet_HttpServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(LoginNet_HttpServerPlugin);
}

void LoginNet_HttpServerPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, ILoginNet_HttpServerModule, LoginNet_HttpServerModule)
}

void LoginNet_HttpServerPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, ILoginNet_HttpServerModule, LoginNet_HttpServerModule)
}