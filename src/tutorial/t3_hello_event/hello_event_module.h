

#ifndef NF_HELLO_WORLD3_H
#define NF_HELLO_WORLD3_H

#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIElementModule.h"
#include "NFComm/NFPluginModule/NFIEventModule.h"
#include "NFComm/NFPluginModule/NFIScheduleModule.h"

class IHelloEventModule
	: public IModule
{

};

class HelloEventModule
    : public IHelloEventModule
{
public:
    HelloEventModule(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool AfterInit();

    virtual bool Execute();

    virtual bool BeforeShut();
    virtual bool Shut();

protected:
    int OnEvent(const Guid& self, const int event, const DataList& arg);
    int OnClassCallBackEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT event, const DataList& arg);
    int OnPropertyCallBackEvent( const Guid& self, const std::string& propertyName, const NFData& oldVarList, const NFData& newVarList, const int64_t reason);
    int OnPropertyStrCallBackEvent( const Guid& self, const std::string& propertyName, const NFData& oldVarList, const NFData& newVarList, const int64_t reason);

    int OnHeartBeat(const Guid& self, const std::string& heartBeat, const float time, const int count);

protected:
    int64_t mLastTime;
protected:
    NFIKernelModule* m_pKernelModule;
    NFIElementModule* m_pElementModule;
	NFIEventModule* m_pEventModule;
	NFIScheduleModule* m_pScheduleModule;
};

#endif
