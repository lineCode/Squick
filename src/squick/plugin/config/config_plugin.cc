
#include "config_plugin.h"
#include "class_module.h"
#include "element_module.h"
#include "config_module.h"

#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, ConfigPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, ConfigPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////
ConfigPlugin::ConfigPlugin(IPluginManager* p)
{
    pPluginManager = p;
}

const int ConfigPlugin::GetPluginVersion()
{
    return 0;
}

const std::string ConfigPlugin::GetPluginName()
{
	return GET_CLASS_NAME(ConfigPlugin);
}

void ConfigPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, IClassModule, ClassModule)
    REGISTER_MODULE(pPluginManager, IElementModule, NFElementModule)
	REGISTER_MODULE(pPluginManager, ICommonConfigModule, ConfigModule);

}

void ConfigPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IElementModule, NFElementModule)
    UNREGISTER_MODULE(pPluginManager, IClassModule, ClassModule)
	UNREGISTER_MODULE(pPluginManager, ICommonConfigModule, ConfigModule);
}
