
#ifndef SQUICK_PROXYSERVERPLUGIN_H
#define SQUICK_PROXYSERVERPLUGIN_H

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"


class ProxyLogicPlugin : public IPlugin
{
public:
    ProxyLogicPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};

#endif