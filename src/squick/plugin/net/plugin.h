

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

//////////////////////////////////////////////////////////////////////////
class NetPlugin : public IPlugin
{
public:
	NetPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};