

#ifndef SQUICK_LoginSERVERNET_HTTPSERVERPLUGIN_H
#define SQUICK_LoginSERVERNET_HTTPSERVERPLUGIN_H
///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef NFLoginNET_HTTPSERVERPLUGIN_EXPORTS
#define NFLoginNET_HTTPSERVERPLUGIN_API __declspec(dllexport)
#else
#define NFLoginNET_HTTPSERVERPLUGIN_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
class LoginNet_HttpServerPlugin : public IPlugin
{
public:
	LoginNet_HttpServerPlugin(IPluginManager* p)
	{
		pPluginManager = p;
	}
	virtual const int GetPluginVersion();

	virtual const std::string GetPluginName();

	virtual void Install();

	virtual void Uninstall();
};

#endif

