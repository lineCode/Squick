

#include "navigation_module.h"
#include "squick/struct/protocol_define.h"

bool NavigationModule::Init()
{
	m_pLogModule = pPluginManager->FindModule<ILogModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();

	SQUICK_SHARE_PTR<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Scene::ThisName());
	if (xLogicClass)
	{
		const std::vector<std::string>& strIdList = xLogicClass->GetIDList();

		for (int i = 0; i < strIdList.size(); ++i)
		{
			const std::string& strId = strIdList[i];

			int sceneId = lexical_cast<int>(strIdList[i]);
			std::string navigationResPath = m_pElementModule->GetPropertyManager(strId)->GetPropertyString(SquickProtocol::Scene::NavigationResPath());
			LoadNavigation(sceneId, navigationResPath);

			//const std::string& strId = strIdList[i];
			//INT64 sceneId = elementModule->GetPropertyManager(strId)->GetPropertyInt(SquickProtocol::Scene::SceneID);// lexical_cast<std::string, INT16>());
			//std::string navigationResPath = elementModule->GetPropertyManager(strId)->GetPropertyString(SquickProtocol::Scene::NavigationResPath());
			//loadNavigation(sceneId, navigationResPath);
			//std::ostringstream strLog;
			//strLog << "strId: (" << strId.c_str() << ") is destroyed!\n";
			//m_pLogModule->LogInfo(NULL_OBJECT, strLog, __FUNCTION__, __LINE__);
			/*elementModule->
			int sceneID = lexical_cast<int>(strIdList[i]);*/
		}
	}
    return true;
}

bool NavigationModule::AfterInit()
{
    return true;
}

SQUICK_SHARE_PTR<NFNavigationHandle> NavigationModule::LoadNavigation(INT64 scendId, string resPath)
{
	if (resPath == "")
		return NULL;

	std::unordered_map<INT64, SQUICK_SHARE_PTR<NFNavigationHandle>>::iterator iter = m_Navhandles.find(scendId);
	if (iter != m_Navhandles.end())
	{
		return iter->second;
	}

	SQUICK_SHARE_PTR<NFNavigationHandle> pNavigationHandle = NULL;
	pNavigationHandle = NFNavigationHandle::Create(resPath);
	m_Navhandles[scendId] = pNavigationHandle;
	return pNavigationHandle;
}

bool NavigationModule::ExistNavigation(INT64 scendId)
{
	return m_Navhandles.find(scendId) != m_Navhandles.end();
}

bool NavigationModule::RemoveNavigation(INT64 scendId)
{
	std::unordered_map<INT64, SQUICK_SHARE_PTR<NFNavigationHandle>>::iterator iter = m_Navhandles.find(scendId);
	if (m_Navhandles.find(scendId) != m_Navhandles.end())
	{
		m_Navhandles.erase(iter);

		std::ostringstream strLog;
		strLog << "Navigation::removeNavigation: (" << scendId << ") is destroyed!\n";
		m_pLogModule->LogInfo(strLog, __FUNCTION__, __LINE__);
		return true;
	}

	return false;
}

SQUICK_SHARE_PTR<NFNavigationHandle> NavigationModule::FindNavigation(INT64 scendId)
{
	std::unordered_map<INT64, SQUICK_SHARE_PTR<NFNavigationHandle>>::iterator iter = m_Navhandles.find(scendId);
	if (m_Navhandles.find(scendId) != m_Navhandles.end())
	{
		if (iter->second == NULL)
		{
			return NULL;
		}
		return iter->second;
	}
	return NULL;
}

int NavigationModule::FindPath(INT64 scendId, const Vector3& start, const Vector3& end, std::vector<Vector3>& paths)
{
	SQUICK_SHARE_PTR<NFNavigationHandle> pNavMeshHandle = FindNavigation(scendId);
	if (pNavMeshHandle)
	{
		return pNavMeshHandle->FindStraightPath(start, end, paths);
	}
	return 0;
}

int NavigationModule::FindRandomPointAroundCircle(INT64 scendId, const Vector3& centerPos, std::vector<Vector3>& points, NFINT32 max_points, float maxRadius)
{
	SQUICK_SHARE_PTR<NFNavigationHandle> pNavMeshHandle = FindNavigation(scendId);
	if (pNavMeshHandle)
	{
		return pNavMeshHandle->FindRandomPointAroundCircle(centerPos, points, max_points, maxRadius);
	}
	return 0;
}

int NavigationModule::Raycast(INT64 scendId, const Vector3& start, const Vector3& end, std::vector<Vector3>& hitPointVec)
{
	SQUICK_SHARE_PTR<NFNavigationHandle> pNavMeshHandle = FindNavigation(scendId);
	if (pNavMeshHandle)
	{
		return pNavMeshHandle->Raycast(start, end, hitPointVec);
	}
	return 0;
}

bool NavigationModule::BeforeShut()
{	
    return true;
}

bool NavigationModule::Shut()
{
    return true;
}

bool NavigationModule::Execute()
{
    return true;
}