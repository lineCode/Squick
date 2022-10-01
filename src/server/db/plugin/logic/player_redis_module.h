

#ifndef SQUICK_PLAYER_REDIS_MODULE_H
#define SQUICK_PLAYER_REDIS_MODULE_H

#include "squick/struct/struct.h"
#include "squick/struct/protocol_define.h"
#include "squick/core/date_time.h"
#include "squick/base/kernel.h"
#include "squick/base/plugin_manager.h"
#include "squick/base/class.h"
#include "squick/base/log.h"
#include "squick/base/element.h"
#include "squick/base/no_sql.h"
#include "squick/base/net.h"

#include "if_player_redis_module.h"
#include "if_account_redis_module.h"
#include "if_common_redis_module.h"

class PlayerRedisModule : public IPlayerRedisModule
{
public:

	PlayerRedisModule(IPluginManager* p);

	virtual bool Init();
	virtual bool Shut();
	virtual bool Execute();

	virtual bool AfterInit();

	virtual bool ExistRoleName(const std::string& strRoleName);
	virtual bool CreateRole(const std::string& account, const std::string& strRoleName, const Guid& id, const int nHomeSceneID);
	virtual bool GetRoleInfo(const std::string& account, std::string& strRoleName, Guid& id);

	virtual bool LoadPlayerData(const Guid& self, SquickStruct::RoleDataPack& roleData);
	virtual bool SavePlayerData(const Guid& self, const SquickStruct::RoleDataPack& roleData);


protected:
	std::string GetOnlineGameServerKey();
	std::string GetOnlineProxyServerKey();

private:


private:
	IClassModule* m_pLogicClassModule;
	IAccountRedisModule* m_pAccountRedisModule;
	INoSqlModule* m_pNoSqlModule;
	ICommonRedisModule* m_pCommonRedisModule;
	IKernelModule* m_pKernelModule;
	ILogModule* m_pLogModule;
};


#endif
