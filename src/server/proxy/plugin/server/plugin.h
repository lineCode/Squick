
#ifndef SQUICK_PROXYSERVERNET_SERVERPLUGIN_H
#define SQUICK_PROXYSERVERNET_SERVERPLUGIN_H

///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFPROXYSERVERNET_SERVERPLUGIN_EXPORTS
#define NFPROXYSERVERNET_SERVERPLUGIN_API __declspec(dllexport)
#else
#define NFPROXYSERVERNET_SERVERPLUGIN_API __declspec(dllimport)
#endif

class ProxyServerNet_ServerPlugin : public IPlugin
{
public:
    ProxyServerNet_ServerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif