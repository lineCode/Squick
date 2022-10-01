#include "squick/plugin_loader/server.h"
#ifndef SQUICK_DYNAMIC_PLUGIN

#include "squick/plugin/actor/actor_plugin.h"
#include "squick/plugin/config/config_plugin.h"
#include "squick/plugin/kernel/kernel_plugin.h"
#include "squick/plugin/log/log_plugin.h"
#include "squick/plugin/lua/lua_script_plugin.h"
#include "squick/plugin/navigation/navigation_plugin.h"
#include "squick/plugin/net/net_plugin.h"
#include "squick/plugin/no_sql/no_sql_plugin.h"
#include "squick/plugin/security/security_plugin.h"
#include "squick/plugin/test/test_plugin.h"

#include "server/plugin/chat/chat_plugin.h"
#include "server/plugin/consume_manager/consume_manager_plugin.h"
#include "server/plugin/inventory/inventory_plugin.h"

#endif

void BasicPluginLoader(IPluginManager* pPluginManager)
{

#ifndef SQUICK_DYNAMIC_PLUGIN

	//for squick-sdk plugins

	CREATE_PLUGIN(pPluginManager, ActorPlugin)
	CREATE_PLUGIN(pPluginManager, ConfigPlugin)
	CREATE_PLUGIN(pPluginManager, KernelPlugin)
	CREATE_PLUGIN(pPluginManager, LogPlugin)
	CREATE_PLUGIN(pPluginManager, LuaScriptPlugin)
	CREATE_PLUGIN(pPluginManager, NavigationPlugin)
	CREATE_PLUGIN(pPluginManager, NetPlugin)
	CREATE_PLUGIN(pPluginManager, NoSqlPlugin)
	CREATE_PLUGIN(pPluginManager, SecurityPlugin)
	
	/*
	// 测试核心模块
	CREATE_PLUGIN(pPluginManager, TestPlugin)

	
	//DB
	CREATE_PLUGIN(pPluginManager, DBLogicPlugin)
	CREATE_PLUGIN(pPluginManager, Net_ClientPlugin)
	CREATE_PLUGIN(pPluginManager, DBNet_ServerPlugin)

	//GAME
	CREATE_PLUGIN(pPluginManager, GameServerNet_ClientPlugin)
	CREATE_PLUGIN(pPluginManager, GameServerNet_ServerPlugin)
	CREATE_PLUGIN(pPluginManager, GameServerPlugin)

	//LOGIN
	CREATE_PLUGIN(pPluginManager, LoginLogicPlugin)
	CREATE_PLUGIN(pPluginManager, LoginNet_ClientPlugin)
	CREATE_PLUGIN(pPluginManager, LoginNet_ServerPlugin)
	CREATE_PLUGIN(pPluginManager, LoginNet_HttpServerPlugin)

	//MASTER
	CREATE_PLUGIN(pPluginManager, MasterNet_HttpServerPlugin)
	CREATE_PLUGIN(pPluginManager, MasterNet_ServerPlugin)

	//PROXY
	CREATE_PLUGIN(pPluginManager, ProxyLogicPlugin)
	CREATE_PLUGIN(pPluginManager, ProxyServerNet_ClientPlugin)
	CREATE_PLUGIN(pPluginManager, ProxyServerNet_ServerPlugin)

	//WORLD
	CREATE_PLUGIN(pPluginManager, WorldNet_ClientPlugin)
	CREATE_PLUGIN(pPluginManager, WorldNet_ServerPlugin)
	
	*/
	//CREATE_PLUGIN(pPluginManager, T1_HelloPlugin)
	#endif
}

void MidWareLoader(IPluginManager* pPluginManager)
{
	//CREATE_PLUGIN(pPluginManager, ChatPlugin)
	//CREATE_PLUGIN(pPluginManager, ConsumeManagerPlugin)
	//CREATE_PLUGIN(pPluginManager, InventoryPlugin)
}
