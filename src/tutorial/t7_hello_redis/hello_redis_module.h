

#ifndef NF_HELLO_WORLD_H
#define NF_HELLO_WORLD_H

#include "NFComm/NFPluginModule/IPlugin.h"
#include "NFComm/NFPluginModule/IPluginManager.h"
#include "NFComm/NFPluginModule/NFINavigationModule.h"
#include "NFComm/NFNoSqlPlugin/NFRedisClient.h"
#include "NFComm/NFCore/NFPerformance.hpp"

/*
IN THIS PLUGIN:
YOU WILL KNOW HOW TO USE THE "IScriptModule" TO CALL LUA SCRIPT
*/


class NFIHelloWorld7
	: public IModule
{

};

class NFHelloWorld7
    : public NFIHelloWorld7
{
public:
    NFHelloWorld7(IPluginManager* p)
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

	bool Test_1();
	bool TestPerformance();

    void TestHash();
    void TestKey();
    void TestList();
    void TestSet();
    void TestSort();
    void TestString();
	void TestPubSub();

protected:
    NFRedisClient mxRedisClient;
};

#endif
