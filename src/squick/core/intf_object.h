
#ifndef SQUICK_INTF_OBJECT_H
#define SQUICK_INTF_OBJECT_H

#include "data_list.h"
#include "intf_record.h"
#include "intf_record_manager.h"
#include "intf_property_manager.h"
#include "squick/base/platform.h"
#include "squick/base/plugin_manager.h"

enum CLASS_OBJECT_EVENT
{
	COE_CREATE_NODATA,
	COE_CREATE_BEFORE_ATTACHDATA,
	COE_CREATE_LOADDATA,
	COE_CREATE_AFTER_ATTACHDATA,
	COE_CREATE_BEFORE_EFFECT,
	COE_CREATE_EFFECTDATA,
	COE_CREATE_AFTER_EFFECT,
	COE_CREATE_READY,
	COE_CREATE_HASDATA,
	COE_CREATE_FINISH,
	COE_CREATE_CLIENT_FINISH,
	COE_BEFOREDESTROY,
	COE_DESTROY,
};

#pragma warning(disable: 4275)
class _NFExport IObject :public MemoryCounter
{
#pragma warning(default: 4275)
private:
	IObject() : MemoryCounter(GET_CLASS_NAME(IObject), 1)
	{
	}

public:
    IObject(Guid self) : MemoryCounter(GET_CLASS_NAME(IObject), 1)
    {
    }

    virtual ~IObject()
	{
	}

    virtual Guid Self() = 0;
	virtual const Vector3& GetPosition() = 0;
	virtual void SetPosition(const Vector3& pos) = 0;

    template<typename BaseType>
    bool AddPropertyCallBack(const std::string& propertyName, BaseType* pBase, int (BaseType::*handler)(const Guid&, const std::string&, const NFData&, const NFData&, const INT64))
    {
        PROPERTY_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
        PROPERTY_EVENT_FUNCTOR_PTR functorPtr(SQUICK_NEW PROPERTY_EVENT_FUNCTOR(functor));
        return AddPropertyCallBack(propertyName, functorPtr);
    }

    template<typename BaseType>
    bool AddRecordCallBack(const std::string& recordName, BaseType* pBase, int (BaseType::*handler)(const Guid&, const RECORD_EVENT_DATA&, const NFData&, const NFData&))
    {
        RECORD_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        RECORD_EVENT_FUNCTOR_PTR functorPtr(SQUICK_NEW RECORD_EVENT_FUNCTOR(functor));
        return AddRecordCallBack(recordName, functorPtr);
    }

    /////////////////////////////////////////////////////////////////
	virtual CLASS_OBJECT_EVENT GetState() = 0;
	virtual void SetState(const CLASS_OBJECT_EVENT eState) = 0;
    virtual bool ObjectReady() = 0;

    virtual bool FindProperty(const std::string& propertyName) = 0;
    virtual SQUICK_SHARE_PTR<IProperty> AddProperty(const std::string& propertyName, const DATA_TYPE varType) = 0;

    virtual bool SetPropertyInt(const std::string& propertyName, const INT64 nValue, const INT64 reason = 0) = 0;
    virtual bool SetPropertyFloat(const std::string& propertyName, const double dwValue, const INT64 reason = 0) = 0;
    virtual bool SetPropertyString(const std::string& propertyName, const std::string& value, const INT64 reason = 0) = 0;
    virtual bool SetPropertyObject(const std::string& propertyName, const Guid& obj, const INT64 reason = 0) = 0;
	virtual bool SetPropertyVector2(const std::string& propertyName, const Vector2& value, const INT64 reason = 0) = 0;
	virtual bool SetPropertyVector3(const std::string& propertyName, const Vector3& value, const INT64 reason = 0) = 0;

    virtual INT64 GetPropertyInt(const std::string& propertyName) = 0;
	virtual int GetPropertyInt32(const std::string& propertyName) = 0;
    virtual double GetPropertyFloat(const std::string& propertyName) = 0;
    virtual const std::string& GetPropertyString(const std::string& propertyName) = 0;
    virtual const Guid& GetPropertyObject(const std::string& propertyName) = 0;
	virtual const Vector2& GetPropertyVector2(const std::string& propertyName) = 0;
	virtual const Vector3& GetPropertyVector3(const std::string& propertyName) = 0;

    virtual SQUICK_SHARE_PTR<IRecord> FindRecord(const std::string& recordName) = 0;

    virtual bool SetRecordInt(const std::string& recordName, const int row, const int col, const INT64 nValue) = 0;
    virtual bool SetRecordFloat(const std::string& recordName, const int row, const int col, const double dwValue) = 0;
    virtual bool SetRecordString(const std::string& recordName, const int row, const int col, const std::string& value) = 0;
    virtual bool SetRecordObject(const std::string& recordName, const int row, const int col, const Guid& obj) = 0;
	virtual bool SetRecordVector2(const std::string& recordName, const int row, const int col, const Vector2& value) = 0;
	virtual bool SetRecordVector3(const std::string& recordName, const int row, const int col, const Vector3& value) = 0;

    virtual bool SetRecordInt(const std::string& recordName, const int row, const std::string& colTag, const INT64 value) = 0;
    virtual bool SetRecordFloat(const std::string& recordName, const int row, const std::string& colTag, const double value) = 0;
    virtual bool SetRecordString(const std::string& recordName, const int row, const std::string& colTag, const std::string& value) = 0;
    virtual bool SetRecordObject(const std::string& recordName, const int row, const std::string& colTag, const Guid& value) = 0;
	virtual bool SetRecordVector2(const std::string& recordName, const int row, const std::string& colTag, const Vector2& value) = 0;
	virtual bool SetRecordVector3(const std::string& recordName, const int row, const std::string& colTag, const Vector3& value) = 0;

    virtual INT64 GetRecordInt(const std::string& recordName, const int row, const int col) = 0;
    virtual double GetRecordFloat(const std::string& recordName, const int row, const int col) = 0;
    virtual const std::string& GetRecordString(const std::string& recordName, const int row, const int col) = 0;
    virtual const Guid& GetRecordObject(const std::string& recordName, const int row, const int col) = 0;
	virtual const Vector2& GetRecordVector2(const std::string& recordName, const int row, const int col) = 0;
	virtual const Vector3& GetRecordVector3(const std::string& recordName, const int row, const int col) = 0;

    virtual INT64 GetRecordInt(const std::string& recordName, const int row, const std::string& colTag) = 0;
    virtual double GetRecordFloat(const std::string& recordName, const int row, const std::string& colTag) = 0;
    virtual const std::string& GetRecordString(const std::string& recordName, const int row, const std::string& colTag) = 0;
    virtual const Guid& GetRecordObject(const std::string& recordName, const int row, const std::string& colTag) = 0;
	virtual const Vector2& GetRecordVector2(const std::string& recordName, const int row, const std::string& colTag) = 0;
	virtual const Vector3& GetRecordVector3(const std::string& recordName, const int row, const std::string& colTag) = 0;

    //  virtual SQUICK_SHARE_PTR<IComponent> AddComponent(const std::string& componentName, const std::string& strLanguageName) = 0;
    //  virtual SQUICK_SHARE_PTR<IComponent> FindComponent(const std::string& componentName) = 0;

    virtual SQUICK_SHARE_PTR<IRecordManager> GetRecordManager() = 0;
    virtual SQUICK_SHARE_PTR<IPropertyManager> GetPropertyManager() = 0;
	virtual void SetRecordManager(SQUICK_SHARE_PTR<IRecordManager> xRecordManager) = 0;
	virtual void SetPropertyManager(SQUICK_SHARE_PTR<IPropertyManager> xPropertyManager) = 0;

protected:
    virtual bool AddRecordCallBack(const std::string& recordName, const RECORD_EVENT_FUNCTOR_PTR& cb) = 0;

    virtual bool AddPropertyCallBack(const std::string& propertyName, const PROPERTY_EVENT_FUNCTOR_PTR& cb) = 0;

protected:
    IPluginManager* m_pPluginManager;

private:
};

#endif
