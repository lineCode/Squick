

#include "plugin.h"
#include "player_redis_module.h"
#include "common_redis_module.h"
#include "account_redis_module.h"

#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, DBLogicPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, DBLogicPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int DBLogicPlugin::GetPluginVersion()
{
    return 0;
}

const std::string DBLogicPlugin::GetPluginName()
{
	return GET_CLASS_NAME(DBLogicPlugin);
}

void DBLogicPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, IPlayerRedisModule, PlayerRedisModule)
	REGISTER_MODULE(pPluginManager, ICommonRedisModule, CommonRedisModule)
	REGISTER_MODULE(pPluginManager, IAccountRedisModule, AccountRedisModule)
}

void DBLogicPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, IAccountRedisModule, AccountRedisModule)
	UNREGISTER_MODULE(pPluginManager, ICommonRedisModule, CommonRedisModule)
	UNREGISTER_MODULE(pPluginManager, IPlayerRedisModule, PlayerRedisModule)
}