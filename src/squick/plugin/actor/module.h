
#ifndef SQUICK_ACTOR_MANAGER_H
#define SQUICK_ACTOR_MANAGER_H

#include <map>
#include <string>
#include <queue>
#include "actor.h"
#include "squick/base/component.h"
#include "squick/base/actor.h"
#include "squick/base/kernel.h"
#include "squick/base/thread_pool.h"
#include "squick/core/queue.h"

class ActorModule
    : public IActorModule
{
public:
	ActorModule(IPluginManager* p);
    virtual ~ActorModule();

    virtual bool Init();

    virtual bool AfterInit();

    virtual bool BeforeShut();

    virtual bool Shut();

    virtual bool Execute();

	virtual SQUICK_SHARE_PTR<IActor> RequireActor();
	virtual SQUICK_SHARE_PTR<IActor> GetActor(const Guid nActorIndex);
	virtual bool ReleaseActor(const Guid nActorIndex);

    virtual bool SendMsgToActor(const Guid actorIndex, const Guid who, const int eventID, const std::string& data, const std::string& arg = "");

	virtual bool AddResult(const ActorMessage& message);

protected:
    virtual bool SendMsgToActor(const Guid actorIndex, const ActorMessage& message);

	virtual bool AddEndFunc(const int subMessageID, ACTOR_PROCESS_FUNCTOR_PTR functorPtr_end);

	virtual bool ExecuteEvent();
	virtual bool ExecuteResultEvent();

private:
    bool test = false;

    IKernelModule* m_pKernelModule;
    IThreadPoolModule* m_pThreadPoolModule;

	std::map<Guid, SQUICK_SHARE_PTR<IActor>> mxActorMap;

	Queue<ActorMessage> mxResultQueue;
	MapEx<int, ACTOR_PROCESS_FUNCTOR> mxEndFunctor;
};

#endif
