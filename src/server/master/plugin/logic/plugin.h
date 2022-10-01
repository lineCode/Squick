
#ifndef SQUICK_MASTERSERVERPLUGIN_H
#define SQUICK_MASTERSERVERPLUGIN_H
///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFMASTERSERVERPLUGIN_EXPORTS
#define NFMASTERSERVERPLUGIN_API __declspec(dllexport)
#else
#define NFMASTERSERVERPLUGIN_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
class MasterServerPlugin : public IPlugin
{
public:
    MasterServerPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif