
#include "server_module.h"
#include "ws_module.h"
#include "plugin.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, ProxyServerNet_ServerPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, ProxyServerNet_ServerPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int ProxyServerNet_ServerPlugin::GetPluginVersion()
{
    return 0;
}

const std::string ProxyServerNet_ServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(ProxyServerNet_ServerPlugin);
}

void ProxyServerNet_ServerPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, IProxyServerNet_ServerModule, ProxyServerNet_ServerModule)
    REGISTER_MODULE(pPluginManager, IProxyServerNet_WSModule, ProxyServerNet_WSModule)

}

void ProxyServerNet_ServerPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IProxyServerNet_WSModule, ProxyServerNet_WSModule)
    UNREGISTER_MODULE(pPluginManager, IProxyServerNet_ServerModule, ProxyServerNet_ServerModule)
}