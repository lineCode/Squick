

#ifndef SQUICK_SECURITY_PLUGIN_H
#define SQUICK_SECURITY_PLUGIN_H

///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class SecurityPlugin : public IPlugin
{
public:
	SecurityPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif