

#include "navigation_module.h"
#include "navigation_data_module.h"
#include "navigation_plugin.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, NavigationPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, NavigationPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int NavigationPlugin::GetPluginVersion()
{
    return 0;
}

const std::string NavigationPlugin::GetPluginName()
{
	return GET_CLASS_NAME(NavigationPlugin);
}

void NavigationPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, INavigationModule, NavigationModule)
    REGISTER_MODULE(pPluginManager, INavigationDataModule, NavigationDataModule)
}

void NavigationPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, INavigationDataModule, NavigationDataModule)
    UNREGISTER_MODULE(pPluginManager, INavigationModule, NavigationModule)
}