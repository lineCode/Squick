
#ifndef SQUICK_MASTERSERVERNET_HTTPSERVERPLUGIN_H
#define SQUICK_MASTERSERVERNET_HTTPSERVERPLUGIN_H
///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFMASTERNET_HTTPSERVERPLUGIN_EXPORTS
#define NFMASTERNET_HTTPSERVERPLUGIN_API __declspec(dllexport)
#else
#define NFMASTERNET_HTTPSERVERPLUGIN_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
class MasterNet_HttpServerPlugin : public IPlugin
{
public:
	MasterNet_HttpServerPlugin(IPluginManager* p)
	{
		pPluginManager = p;
	}
	virtual const int GetPluginVersion();

	virtual const std::string GetPluginName();

	virtual void Install();

	virtual void Uninstall();
};

#endif

