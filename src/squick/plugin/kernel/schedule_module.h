

#ifndef SQUICK_SCHEDULE_MODULE_H
#define SQUICK_SCHEDULE_MODULE_H

#include <iostream>
#include <set>
#include <algorithm>
#include "squick/core/map.h"
#include "squick/core/list.h"
#include "squick/core/performance.h"
#include "squick/core/data_list.h"
#include "squick/core/date_time.h"
#include "squick/base/schedule.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"
#include "squick/base/scene.h"

#if SQUICK_PLATFORM != SQUICK_PLATFORM_WIN
#include "squick/core/exception.h"
#endif

class TickElement
{
public:

	bool operator< (const TickElement& b) const
	{
		return this->triggerTime < b.triggerTime;
	}

	std::string scheduleName;
	INT64 triggerTime;
	Guid self;
};

class NFScheduleModule : public NFIScheduleModule
{
public:
    NFScheduleModule(IPluginManager* p);

	virtual ~NFScheduleModule();

	virtual bool Init();
	virtual bool Execute();

	virtual bool AddSchedule(const Guid self, const std::string& scheduleName, const OBJECT_SCHEDULE_FUNCTOR_PTR& cb, const float time, const int count);
	virtual bool RemoveSchedule(const Guid self);
	virtual bool RemoveSchedule(const Guid self, const std::string& scheduleName);
	virtual bool ExistSchedule(const Guid self, const std::string& scheduleName);
	virtual SQUICK_SHARE_PTR<ScheduleElement> GetSchedule(const Guid self, const std::string& scheduleName);

protected:
	int OnClassCommonEvent(const Guid & self, const std::string & className, const CLASS_OBJECT_EVENT classEvent, const DataList & var);

	int OnGroupCommonEvent(const Guid& self, const int scene, const int group, const int type, const DataList& arg);

protected:
	MapEx<Guid, MapEx<std::string, ScheduleElement >> mObjectScheduleMap;

	std::multiset<TickElement> mScheduleMap;

	ILogModule* m_pLogModule;
	IKernelModule* m_pKernelModule;
	ISceneModule* m_pSceneModule;

};

#endif