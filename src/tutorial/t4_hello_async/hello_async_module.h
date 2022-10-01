

#ifndef NF_HELLO_WORLD4_H
#define NF_HELLO_WORLD4_H

#include <thread>
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIActorModule.h"
#include "NFComm/NFPluginModule/NFIComponent.h"
#include "NFComm/NFPluginModule/NFIThreadPoolModule.h"

/*
IN THIS PLUGIN:
YOU WILL KNOW HOW TO USE THE "NFIActorModule" TO PROCESS IN DIFFERENT CPU
*/


class NFHttpComponent : public NFIComponent
{
public:
	NFHttpComponent() : NFIComponent(typeid(NFHttpComponent).name())
	{
	}

	virtual ~NFHttpComponent()
	{

	}

	virtual bool Init()
	{
		AddMsgHandler(0, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(1, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(2, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(3, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(4, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(5, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(6, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(7, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(8, this, &NFHttpComponent::OnMsgEvent);
		AddMsgHandler(9, this, &NFHttpComponent::OnMsgEvent);

		return true;
	}

	//it's very important to note here:
	//sometimes, the function below not finished but other thread call it at the same time
	//the reason is the main thread post a new message to this actor and the schedulel assigned another thread to take the execution right
	//so, you wouldnot use the data which not thread-safe in this function
	virtual int OnMsgEvent(NFActorMessage& arg)
	{

		std::cout << "Thread: " << std::this_thread::get_id() << " MsgID: " << arg.msgID << " Data:" << arg.data << std::endl;


		return 0;
	}
};

class NFIHelloWorld4Module
	: public IModule
{
};

class NFHelloWorld4Module
    : public NFIHelloWorld4Module
{
public:
    NFHelloWorld4Module(IPluginManager* p)
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
	void RequestAsyEnd(NFActorMessage& actorMessage);
	
protected:
    NFIActorModule* m_pActorModule;
	NFIThreadPoolModule* m_pThreadPoolModule;
};

#endif
