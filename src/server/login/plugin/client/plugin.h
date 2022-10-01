

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFLOGINNET_CLIENTPLUGIN_EXPORTS
#define NFLOGINNET_CLIENTPLUGIN_API __declspec(dllexport)
#else
#define NFLOGINNET_CLIENTPLUGIN_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
class LoginNet_ClientPlugin : public IPlugin
{
public:
    LoginNet_ClientPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
