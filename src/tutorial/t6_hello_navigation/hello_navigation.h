

#ifndef NF_HELLO_WORLD_H
#define NF_HELLO_WORLD_H

#include "NFComm/NFPluginModule/IPlugin.h"
#include "NFComm/NFPluginModule/IPluginManager.h"
#include "NFComm/NFPluginModule/NFINavigationModule.h"

/*
IN THIS PLUGIN:
YOU WILL KNOW HOW TO USE THE "INavigationModule" TO FIND THE PATH FOR AI OBJECT
*/

class NFIHelloWorld6
	: public IModule
{

};

class NFHelloWorld6
    : public NFIHelloWorld6
{
public:
    NFHelloWorld6(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool AfterInit();

    virtual bool Execute();

    virtual bool BeforeShut();
    virtual bool Shut();

protected:
	NFINavigationModule* m_pNavigationModule;
};

#endif
