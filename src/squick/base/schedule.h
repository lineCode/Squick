

#ifndef SQUICK_INTF_SCHEDULE_MODULE_H
#define SQUICK_INTF_SCHEDULE_MODULE_H

#include <string>
#include "squick/core/map.h"
#include "squick/core/list.h"
#include "squick/core/data_list.h"
#include "squick/core/date_time.h"
#include "squick/base/module.h"
//int ScheduleFunction(const Guid& self, const std::string& name, const float time, const int count);
typedef std::function<int(const Guid&, const std::string&, const float, const int)> OBJECT_SCHEDULE_FUNCTOR;
typedef SQUICK_SHARE_PTR<OBJECT_SCHEDULE_FUNCTOR> OBJECT_SCHEDULE_FUNCTOR_PTR;//HEART


class  ScheduleElement
{
public:
	ScheduleElement()
	{
		mstrScheduleName = "";
		mfIntervalTime = 0.0f;
		mnTriggerTime = 0;
		mnRemainCount = -1;

		static INT64 elementID = 0;
		id = elementID++;
	};

	virtual ~ScheduleElement()
	{
	}

	void DoHeartBeatEvent(INT64 nowTime);

	std::string mstrScheduleName;
	float mfIntervalTime;
	INT64 mnTriggerTime;
	int mnRemainCount;
	INT64 id;

	Guid self;

	List<OBJECT_SCHEDULE_FUNCTOR_PTR> mxObjectFunctor;
};

class NFIScheduleModule
	:public  IModule
{
public:
	virtual ~NFIScheduleModule() {}

	///for object
	virtual bool RemoveSchedule(const Guid self) = 0;
	virtual bool RemoveSchedule(const Guid self, const std::string& scheduleName) = 0;
	virtual bool ExistSchedule(const Guid self, const std::string& scheduleName) = 0;
	virtual SQUICK_SHARE_PTR<ScheduleElement> GetSchedule(const Guid self, const std::string& scheduleName) = 0;

	template<typename BaseType>
	bool AddSchedule(const Guid self, const std::string& scheduleName, BaseType* pBase, int (BaseType::*handler)(const Guid& self, const std::string& scheduleName, const float time, const int count), const float fIntervalTime, const int count)
	{
		OBJECT_SCHEDULE_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		OBJECT_SCHEDULE_FUNCTOR_PTR functorPtr(SQUICK_NEW OBJECT_SCHEDULE_FUNCTOR(functor));
		return AddSchedule(self, scheduleName, functorPtr, fIntervalTime, count);
	}

protected:
	virtual bool AddSchedule(const Guid self, const std::string& scheduleName, const OBJECT_SCHEDULE_FUNCTOR_PTR& cb, const float time, const int count) = 0;
};

#endif
