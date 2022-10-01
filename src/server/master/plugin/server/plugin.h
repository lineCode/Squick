

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFMASTERNET_SERVERPLUGIN_EXPORTS
#define NFMASTERNET_SERVERPLUGIN_API __declspec(dllexport)
#else
#define NFMASTERNET_SERVERPLUGIN_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
class MasterNet_ServerPlugin : public IPlugin
{
public:
    MasterNet_ServerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};

