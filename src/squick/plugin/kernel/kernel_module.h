

#ifndef SQUICK_KERNEL_MODULE_H
#define SQUICK_KERNEL_MODULE_H

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include "squick/core/intf_object.h"
#include "squick/core/data_list.h"
#include "squick/core/intf_record.h"
#include "squick/base/guid.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/scene.h"
#include "squick/base/schedule.h"
#include "squick/base/event.h"
#include "squick/base/cell.h"
#include "squick/base/thread_pool.h"


class NFKernelModule
    : public IKernelModule,
  public MapEx<Guid, IObject>
{
public:
    NFKernelModule(IPluginManager* p);
    virtual ~NFKernelModule();

    virtual bool Init();
    virtual bool Shut();

    virtual bool BeforeShut();
    virtual bool AfterInit();

    virtual bool Execute();

    ///////////////////////////////////////////////////////////////////////

    virtual bool ExistScene(const int sceneID);

	virtual bool ExistObject(const Guid& ident);
    virtual bool ObjectReady(const Guid& ident);
	virtual bool ExistObject(const Guid& ident, const int sceneID, const int groupID);

    virtual SQUICK_SHARE_PTR<IObject> GetObject(const Guid& ident);
    virtual SQUICK_SHARE_PTR<IObject> CreateObject(const Guid& self, const int sceneID, const int groupID, const std::string& className, const std::string& configIndex, const DataList& arg);

    virtual bool DestroyAll();
    virtual bool DestroySelf(const Guid& self);
    virtual bool DestroyObject(const Guid& self);

    //////////////////////////////////////////////////////////////////////////
    virtual bool FindProperty(const Guid& self, const std::string& propertyName);

    virtual bool SetPropertyInt(const Guid& self, const std::string& propertyName, const INT64 nValue, const INT64 reason = 0);
    virtual bool SetPropertyFloat(const Guid& self, const std::string& propertyName, const double dValue, const INT64 reason = 0);
    virtual bool SetPropertyString(const Guid& self, const std::string& propertyName, const std::string& value, const INT64 reason = 0);
    virtual bool SetPropertyObject(const Guid& self, const std::string& propertyName, const Guid& objectValue, const INT64 reason = 0);
	virtual bool SetPropertyVector2(const Guid& self, const std::string& propertyName, const Vector2& value, const INT64 reason = 0);
	virtual bool SetPropertyVector3(const Guid& self, const std::string& propertyName, const Vector3& value, const INT64 reason = 0);

    virtual INT64 GetPropertyInt(const Guid& self, const std::string& propertyName);
	virtual int GetPropertyInt32(const Guid& self, const std::string& propertyName);	//equal to (int)GetPropertyInt(...), to remove C4244 warning
    virtual double GetPropertyFloat(const Guid& self, const std::string& propertyName);
    virtual const std::string& GetPropertyString(const Guid& self, const std::string& propertyName);
    virtual const Guid& GetPropertyObject(const Guid& self, const std::string& propertyName);
	virtual const Vector2& GetPropertyVector2(const Guid& self, const std::string& propertyName);
	virtual const Vector3& GetPropertyVector3(const Guid& self, const std::string& propertyName);

    //////////////////////////////////////////////////////////////////////////
    virtual SQUICK_SHARE_PTR<IRecord> FindRecord(const Guid& self, const std::string& recordName);
    virtual bool ClearRecord(const Guid& self, const std::string& recordName);

    virtual bool SetRecordInt(const Guid& self, const std::string& recordName, const int row, const int col, const INT64 nValue);
    virtual bool SetRecordFloat(const Guid& self, const std::string& recordName, const int row, const int col, const double dwValue);
    virtual bool SetRecordString(const Guid& self, const std::string& recordName, const int row, const int col, const std::string& value);
    virtual bool SetRecordObject(const Guid& self, const std::string& recordName, const int row, const int col, const Guid& objectValue);
	virtual bool SetRecordVector2(const Guid& self, const std::string& recordName, const int row, const int col, const Vector2& value);
	virtual bool SetRecordVector3(const Guid& self, const std::string& recordName, const int row, const int col, const Vector3& value);

    virtual bool SetRecordInt(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const INT64 value);
    virtual bool SetRecordFloat(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const double value);
    virtual bool SetRecordString(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const std::string& value);
    virtual bool SetRecordObject(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const Guid& value);
	virtual bool SetRecordVector2(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const Vector2& value);
	virtual bool SetRecordVector3(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const Vector3& value);

    virtual INT64 GetRecordInt(const Guid& self, const std::string& recordName, const int row, const int col);
    virtual double GetRecordFloat(const Guid& self, const std::string& recordName, const int row, const int col);
    virtual const std::string& GetRecordString(const Guid& self, const std::string& recordName, const int row, const int col);
    virtual const Guid& GetRecordObject(const Guid& self, const std::string& recordName, const int row, const int col);
	virtual const Vector2& GetRecordVector2(const Guid& self, const std::string& recordName, const int row, const int col);
	virtual const Vector3& GetRecordVector3(const Guid& self, const std::string& recordName, const int row, const int col);

    virtual INT64 GetRecordInt(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
    virtual double GetRecordFloat(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
    virtual const std::string& GetRecordString(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
    virtual const Guid& GetRecordObject(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
	virtual const Vector2& GetRecordVector2(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
	virtual const Vector3& GetRecordVector3(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);

    ////////////////////////////////////////////////////////////////
    virtual Guid CreateGUID();

    virtual bool CreateScene(const int sceneID);
    virtual bool DestroyScene(const int sceneID);

    virtual int GetOnLineCount();
    virtual int GetMaxOnLineCount();

    virtual int RequestGroupScene(const int sceneID);
    virtual bool ReleaseGroupScene(const int sceneID, const int groupID);
    virtual bool ExitGroupScene(const int sceneID, const int groupID);

	virtual int GetGroupObjectList(const int sceneID, const int groupID, const bool bPlayer, const Guid& noSelf);
	virtual bool GetGroupObjectList(const int sceneID, const int groupID, DataList& list);
	virtual bool GetGroupObjectList(const int sceneID, const int groupID, DataList& list, const Guid& noSelf);
	virtual bool GetGroupObjectList(const int sceneID, const int groupID, DataList& list, const bool bPlayer);
	virtual bool GetGroupObjectList(const int sceneID, const int groupID, DataList& list, const bool bPlayer, const Guid& noSelf);
	virtual bool GetGroupObjectList(const int sceneID, const int groupID, const std::string& className, DataList& list);
	virtual bool GetGroupObjectList(const int sceneID, const int groupID, const std::string& className, DataList& list, const Guid& noSelf);
	
	virtual int GetObjectByProperty(const int sceneID, const int groupID, const std::string& propertyName, const DataList& valueArgArg, DataList& list);

	virtual int Random(int nStart, int nEnd);//return [nStart, nEnd)
	virtual float Random();//return [0f, 1f)

    //////////////////////////////////////////////////////////////////////////
    virtual bool LogStack();
    virtual bool LogInfo(const Guid ident);
    virtual bool LogSelfInfo(const Guid ident);

    //////////////////////////////////////////////////////////////////////////

    virtual bool DoEvent(const Guid& self, const std::string& className, CLASS_OBJECT_EVENT eEvent, const DataList& valueList);

protected:

    
    virtual bool RegisterCommonClassEvent(const CLASS_EVENT_FUNCTOR_PTR& cb);
    virtual bool RegisterCommonPropertyEvent(const PROPERTY_EVENT_FUNCTOR_PTR& cb);
    virtual bool RegisterCommonRecordEvent(const RECORD_EVENT_FUNCTOR_PTR& cb);

	virtual bool RegisterClassPropertyEvent(const std::string& className, const PROPERTY_EVENT_FUNCTOR_PTR& cb);
	virtual bool RegisterClassRecordEvent(const std::string& className, const RECORD_EVENT_FUNCTOR_PTR& cb);
protected:

    virtual bool AddClassCallBack(const std::string& className, const CLASS_EVENT_FUNCTOR_PTR& cb);

    void InitRandom();

    int OnClassCommonEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var);
    int OnPropertyCommonEvent(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const INT64 reason);
    int OnRecordCommonEvent(const Guid& self, const RECORD_EVENT_DATA& eventData, const NFData& oldVar, const NFData& newVar);

    void ProcessMemFree();

protected:

    std::list<Guid> mtDeleteSelfList;

    //////////////////////////////////////////////////////////////////////////
    
    std::list<CLASS_EVENT_FUNCTOR_PTR> mtCommonClassCallBackList;
    std::list<PROPERTY_EVENT_FUNCTOR_PTR> mtCommonPropertyCallBackList;
    std::list<RECORD_EVENT_FUNCTOR_PTR> mtCommonRecordCallBackList;

	std::map<std::string, std::list<PROPERTY_EVENT_FUNCTOR_PTR>> mtClassPropertyCallBackList;
	std::map<std::string, std::list<RECORD_EVENT_FUNCTOR_PTR>> mtClassRecordCallBackList;

private:
    std::vector<float> mvRandom;
	int nGUIDIndex;
    //int mnRandomPos;
	decltype(mvRandom.cbegin()) mxRandomItor;

    Guid mnCurExeObject;
    INT64 nLastTime;

	ISceneModule* m_pSceneModule;
    ILogModule* m_pLogModule;
    IClassModule* m_pClassModule;
    IElementModule* m_pElementModule;
	NFIScheduleModule* m_pScheduleModule;
	IEventModule* m_pEventModule;
    NFICellModule* m_pCellModule;
    IThreadPoolModule* m_pThreadPoolModule;

};

#endif
