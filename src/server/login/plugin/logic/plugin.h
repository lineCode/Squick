
#ifndef SQUICK_LOGINLOGICPLUGIN_MODULE_H
#define SQUICK_LOGINLOGICPLUGIN_MODULE_H

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFLOGINLOGICPLUGIN_EXPORTS
#define NFLOGINLOGICPLUGIN_API __declspec(dllexport)
#else
#define NFLOGINLOGICPLUGIN_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
class LoginLogicPlugin : public IPlugin
{
public:
    LoginLogicPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif