

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFDBNET_SERVERPLUGIN_EXPORTS
#define NFDBNET_SERVERPLUGIN_API __declspec(dllexport)
#else
#define NFDBNET_SERVERPLUGIN_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
class DBNet_ServerPlugin : public IPlugin
{
public:
	DBNet_ServerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};