

#ifndef SQUICK_INTF_ACCOUNT_REDIS_MODULE_H
#define SQUICK_INTF_ACCOUNT_REDIS_MODULE_H

#include <squick/base/module.h>

class IAccountRedisModule
    : public IModule
{

public:
	virtual bool VerifyAccount(const std::string& account, const std::string& strPwd) = 0;
	virtual bool AddAccount(const std::string& account, const std::string& strPwd) = 0;
	virtual bool ExistAccount(const std::string& account) = 0;
};

#endif