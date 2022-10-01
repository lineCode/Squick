

#include "plugin.h"
#include "logic_module.h"

//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, LoginLogicPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, LoginLogicPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int LoginLogicPlugin::GetPluginVersion()
{
    return 0;
}

const std::string LoginLogicPlugin::GetPluginName()
{
    return GET_CLASS_NAME(LoginLogicPlugin);
}

void LoginLogicPlugin::Install()
{

    REGISTER_MODULE(pPluginManager, ILoginLogicModule, LoginLogicModule)

}

void LoginLogicPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, ILoginLogicModule, LoginLogicModule)
}
