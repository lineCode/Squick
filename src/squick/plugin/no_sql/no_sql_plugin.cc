

#include "no_sql_plugin.h"
#include "no_sql_module.h"

#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, NoSqlPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, NoSqlPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int NoSqlPlugin::GetPluginVersion()
{
    return 0;
}

const std::string NoSqlPlugin::GetPluginName()
{
	return GET_CLASS_NAME(NoSqlPlugin);
}

void NoSqlPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, INoSqlModule, NoSqlModule)
}

void NoSqlPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, INoSqlModule, NoSqlModule)
}