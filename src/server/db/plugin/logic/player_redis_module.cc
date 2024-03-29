
#include "player_redis_module.h"
#include "common_redis_module.h"

PlayerRedisModule::PlayerRedisModule(IPluginManager * p)
{
	pPluginManager = p;
}

bool PlayerRedisModule::Init()
{
	m_pLogicClassModule = pPluginManager->FindModule<IClassModule>();
	m_pNoSqlModule = pPluginManager->FindModule<INoSqlModule>();
	m_pCommonRedisModule = pPluginManager->FindModule<ICommonRedisModule>();
	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pLogModule = pPluginManager->FindModule<ILogModule>();
	m_pAccountRedisModule = pPluginManager->FindModule<IAccountRedisModule>();
	
	return true;
}

bool PlayerRedisModule::Shut()
{
	return true;
}

bool PlayerRedisModule::Execute()
{
	return true;
}

bool PlayerRedisModule::AfterInit()
{

	return true;
}

bool PlayerRedisModule::LoadPlayerData(const Guid & self, SquickStruct::RoleDataPack& roleData)
{
	CommonRedisModule* pCommonRedisModule = (CommonRedisModule*)(m_pCommonRedisModule);

	SQUICK_SHARE_PTR<IPropertyManager> xPropertyManager = m_pCommonRedisModule->GetPropertyInfo(self.ToString(), SquickProtocol::Player::ThisName(), false, true);
	if (xPropertyManager)
	{
		*(roleData.mutable_property()->mutable_player_id()) = INetModule::StructToProtobuf(self);

		pCommonRedisModule->ConvertPropertyManagerToPB(xPropertyManager, roleData.mutable_property(), false, true);

		pCommonRedisModule->GetRecordInfo(self.ToString(), SquickProtocol::Player::ThisName(), roleData.mutable_record(), false, true);
		
		return true;
	}

	
	m_pLogModule->LogError(self, "loaded data false", __FUNCTION__, __LINE__);

	return false;
}

bool PlayerRedisModule::SavePlayerData(const Guid & self, const SquickStruct::RoleDataPack& roleData)
{
	CommonRedisModule* pCommonRedisModule = (CommonRedisModule*)m_pCommonRedisModule;

	SQUICK_SHARE_PTR<IPropertyManager> xPropManager = pCommonRedisModule->NewPropertyManager(SquickProtocol::Player::ThisName());
	if (pCommonRedisModule->ConvertPBToPropertyManager(roleData.property(), xPropManager))
	{
		m_pCommonRedisModule->SavePropertyInfo(self.ToString(), xPropManager, false, true);
	}

	pCommonRedisModule->SaveRecordInfo(self.ToString(), roleData.record(), -1);

	return true;
}

std::string PlayerRedisModule::GetOnlineGameServerKey()
{
	//if (strValue == "**nonexistent-key**")
	return "OnlineGameKey";
}

std::string PlayerRedisModule::GetOnlineProxyServerKey()
{
	return "OnlineProxyKey";
}


bool PlayerRedisModule::ExistRoleName(const std::string & strRoleName)
{
	SQUICK_SHARE_PTR<IRedisClient> xNoSqlDriver = m_pNoSqlModule->GetDriverBySuitConsistent();
	if (xNoSqlDriver)
	{
		return xNoSqlDriver->EXISTS(strRoleName);
	}

	return false;
}

bool PlayerRedisModule::CreateRole(const std::string & account, const std::string & strRoleName, const Guid & id, const int nHomeSceneID)
{
	const std::string strAccountKey = m_pCommonRedisModule->GetAccountCacheKey(account);
	SQUICK_SHARE_PTR<IRedisClient> xNoSqlDriver = m_pNoSqlModule->GetDriverBySuit(account);
	if (xNoSqlDriver)
	{
		if (!xNoSqlDriver->EXISTS(strAccountKey))
		{
			m_pAccountRedisModule->AddAccount(account, account);
		}

		if (xNoSqlDriver->EXISTS(strAccountKey) && !xNoSqlDriver->EXISTS(strRoleName))
		{
			std::vector<std::string> vecFields;
			std::vector<std::string> vecValues;

			vecFields.push_back(SquickProtocol::Player::Name());
			vecFields.push_back(SquickProtocol::Player::ID());

			vecValues.push_back(strRoleName);
			vecValues.push_back(id.ToString());

			xNoSqlDriver->HMSET(strAccountKey, vecFields, vecValues);

			SQUICK_SHARE_PTR<IRedisClient> xRoleNameNoSqlDriver = m_pNoSqlModule->GetDriverBySuitConsistent();
			if (xRoleNameNoSqlDriver)
			{
				//the name ref to the guid
				xRoleNameNoSqlDriver->HSET(strRoleName, SquickProtocol::Player::ID(), id.ToString());
			}

			SQUICK_SHARE_PTR<IPropertyManager> xPropertyManager = m_pCommonRedisModule->NewPropertyManager(SquickProtocol::Player::ThisName());
			if (xPropertyManager)
			{
				SQUICK_SHARE_PTR<IProperty> xProperty = xPropertyManager->GetElement(SquickProtocol::Player::Account());
				if (xProperty)
				{
					xProperty->SetString(account);
				}

				xProperty = xPropertyManager->GetElement(SquickProtocol::Player::Level());
				if (xProperty)
				{
					xProperty->SetInt(0);
				}

				xProperty = xPropertyManager->GetElement(SquickProtocol::Player::Name());
				if (xProperty)
				{
					xProperty->SetString(strRoleName);
				}

				m_pCommonRedisModule->SavePropertyInfo(id.ToString(), xPropertyManager, false, true);
			}

			return true;
		}
	}

	return false;
}

bool PlayerRedisModule::GetRoleInfo(const std::string & account, std::string & strRoleName, Guid & id)
{
	std::string strAccountKey = m_pCommonRedisModule->GetAccountCacheKey(account);
	SQUICK_SHARE_PTR<IRedisClient> xNoSqlDriver = m_pNoSqlModule->GetDriverBySuit(account);
	if (xNoSqlDriver)
	{
		if (xNoSqlDriver->EXISTS(strAccountKey))
		{
			std::string strID;
			bool bRoleNameRet = xNoSqlDriver->HGET(strAccountKey, SquickProtocol::Player::Name(), strRoleName);
			bool bRoleIDRet = xNoSqlDriver->HGET(strAccountKey, SquickProtocol::Player::ID(), strID);
			if (bRoleNameRet && bRoleIDRet
				&& !strRoleName.empty() && !strID.empty())
			{
				return id.FromString(strID);
			}

			return false;
		}
	}

	return false;
}
