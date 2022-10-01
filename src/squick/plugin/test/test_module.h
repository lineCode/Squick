

#ifndef SQUICK_TEST_MODULE_H
#define SQUICK_TEST_MODULE_H

#include "squick/base/log.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"

class NFITestModule
	: public IModule
{
};

class TestModule
    : public NFITestModule
{
public:
    TestModule( IPluginManager* p )
    {
        m_bIsExecute = true;
        pPluginManager = p;
    }

    virtual ~TestModule() {};

    virtual bool Awake();
    virtual bool Init();
    virtual bool AfterInit();
    virtual bool CheckConfig();
    virtual bool ReadyExecute();
    virtual bool Execute();
    virtual bool BeforeShut();
    virtual bool Shut();
    virtual bool Finalize();
    virtual bool OnReloadPlugin();


protected:
    int Factorial(int n);

private:
};


#endif
