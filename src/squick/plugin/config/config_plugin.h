
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

//////////////////////////////////////////////////////////////////////////
class ConfigPlugin : public IPlugin
{
public:
    ConfigPlugin(IPluginManager* p);

    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
