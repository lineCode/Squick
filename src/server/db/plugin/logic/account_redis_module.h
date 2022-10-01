

#ifndef SQUICK_ACCOUNT_REDIS_MODULE_H
#define SQUICK_ACCOUNT_REDIS_MODULE_H

#include "squick/struct/struct.h"
#include "squick/struct/protocol_define.h"
#include "squick/base/class.h"
#include "squick/base/log.h"
#include "squick/base/element.h"
#include "squick/base/no_sql.h"
#include "squick/base/plugin_manager.h"
#include "squick/base/kernel.h"


#include "if_player_redis_module.h"
#include "if_account_redis_module.h"
#include "if_common_redis_module.h"

class AccountRedisModule : public IAccountRedisModule
{
public:

	AccountRedisModule(IPluginManager* p)
	{
		pPluginManager = p;
	}

	virtual bool Init();
	virtual bool Shut();
	virtual bool Execute();

	virtual bool AfterInit();

	virtual bool VerifyAccount(const std::string& account, const std::string& strPwd);
	virtual bool AddAccount(const std::string& account, const std::string& strPwd);
	virtual bool ExistAccount(const std::string& account);


protected:

private:
	IClassModule* m_pLogicClassModule;
	INoSqlModule* m_pNoSqlModule;
	ICommonRedisModule* m_pCommonRedisModule;
	IKernelModule* m_pKernelModule;
};


#endif
