

#ifndef SQUICK_DATANOSQL_MODULE_H
#define SQUICK_DATANOSQL_MODULE_H

#include "redis_client.h"
#include "squick/base/platform.h"
#include "squick/base/plugin_manager.h"
#include "squick/base/no_sql.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/log.h"

class NoSqlModule
	: public INoSqlModule
{
public:

	NoSqlModule(IPluginManager* p);
	virtual ~NoSqlModule();

	virtual bool Init();
	virtual bool Shut();
	virtual bool Execute();
	virtual bool AfterInit();
	
	virtual bool Connect(const std::string& ip, const int nPort, const std::string& strPass) { return false; };
	virtual bool Enable();
	virtual bool Busy();
	virtual bool KeepLive();


	virtual bool AddConnectSql(const std::string& strID, const std::string& ip);
	virtual bool AddConnectSql(const std::string& strID, const std::string& ip, const int nPort);
	virtual bool AddConnectSql(const std::string& strID, const std::string& ip, const int nPort, const std::string& strPass);

	virtual List<std::string> GetDriverIdList();
	virtual SQUICK_SHARE_PTR<IRedisClient> GetDriver(const std::string& strID);
	virtual SQUICK_SHARE_PTR<IRedisClient> GetDriverBySuitRandom();
	virtual SQUICK_SHARE_PTR<IRedisClient> GetDriverBySuitConsistent();
	virtual SQUICK_SHARE_PTR<IRedisClient> GetDriverBySuit(const std::string& strHash);
	//virtual SQUICK_SHARE_PTR<IRedisClient> GetDriverBySuit(const int nHash);
	virtual bool RemoveConnectSql(const std::string& strID);

protected:
	void CheckConnect();

protected:
	INT64 mLastCheckTime;
	IClassModule* m_pClassModule;
	IElementModule* m_pElementModule;
	ILogModule* m_pLogModule;

	NFConsistentHashMapEx<std::string, IRedisClient> mxNoSqlDriver;

};

#endif