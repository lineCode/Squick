

#include "plugin.h"
#include "http_server_module.h"
//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

	CREATE_PLUGIN(pm, MasterNet_HttpServerPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
	DESTROY_PLUGIN(pm, MasterNet_HttpServerPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int MasterNet_HttpServerPlugin::GetPluginVersion()
{
	return 0;
}

const std::string MasterNet_HttpServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(MasterNet_HttpServerPlugin);
}

void MasterNet_HttpServerPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, IMasterNet_HttpServerModule, MasterNet_HttpServerModule)
}

void MasterNet_HttpServerPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, IMasterNet_HttpServerModule, MasterNet_HttpServerModule)
}