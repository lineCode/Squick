
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFLOGINNET_SERVERPLUGIN_EXPORTS
#define NFLOGINNET_SERVERPLUGIN_API __declspec(dllexport)
#else
#define NFLOGINNET_SERVERPLUGIN_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
class LoginNet_ServerPlugin : public IPlugin
{
public:
    LoginNet_ServerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
