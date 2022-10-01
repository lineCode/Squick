

#ifndef SQUICK_PROXYSERVER_NETCLIENTPLUGIN_MODULE_H
#define SQUICK_PROXYSERVER_NETCLIENTPLUGIN_MODULE_H
///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFPROXYSERVERNET_CLIENTPLUGIN_EXPORTS
#define NFPROXYSERVERNET_CLIENTPLUGIN_API __declspec(dllexport)
#else
#define NFPROXYSERVERNET_CLIENTPLUGIN_API __declspec(dllimport)
#endif

class ProxyServerNet_ClientPlugin : public IPlugin
{
public:
    ProxyServerNet_ClientPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};

#endif