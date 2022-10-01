

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFWORLDNET_SERVERPLUGIN_EXPORTS
#define NFWORLDNET_SERVERPLUGIN_API __declspec(dllexport)
#else
#define NFWORLDNET_SERVERPLUGIN_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
class WorldNet_ServerPlugin : public IPlugin
{
public:
    WorldNet_ServerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};