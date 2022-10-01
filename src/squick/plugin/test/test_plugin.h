

#ifndef SQUICK_TEST_PLUGIN_H
#define SQUICK_TEST_PLUGIN_H

///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class TestPlugin : public IPlugin
{
public:
	TestPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif //SQUICK_TASK_PLUGIN_H