
#include "log_plugin.h"
#include "log_module.h"

#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, LogPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, LogPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int LogPlugin::GetPluginVersion()
{
    return 0;
}

const std::string LogPlugin::GetPluginName()
{
	return GET_CLASS_NAME(LogPlugin);
}

void LogPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, ILogModule, LogModule)
}

void LogPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, ILogModule, LogModule)
}