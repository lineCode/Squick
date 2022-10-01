

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFDBNET_CLIENTPLUGIN_EXPORTS
#define NFDBNET_CLIENTPLUGIN_API __declspec(dllexport)
#else
#define NFDBNET_CLIENTPLUGIN_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
class Net_ClientPlugin : public IPlugin
{
public:
    Net_ClientPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};

