#pragma once

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class T1_HelloPlugin : public IPlugin
{
public:
    T1_HelloPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};

