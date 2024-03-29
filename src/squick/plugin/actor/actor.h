

#ifndef SQUICK_ACTOR_H
#define SQUICK_ACTOR_H

#include <map>
#include <string>
#include "squick/core/queue.h"
#include "squick/base/guid.h"
#include "squick/base/platform.h"
#include "squick/base/component.h"
#include "squick/base/actor.h"

class Actor
    : public IActor
{
public:
	Actor(const Guid id, IActorModule* pModule);
	virtual ~Actor();

	const Guid ID();
	
    virtual bool Execute();

    virtual bool AddComponent(SQUICK_SHARE_PTR<IComponent> component);
	virtual bool RemoveComponent(const std::string& componentName);
	virtual SQUICK_SHARE_PTR<IComponent> FindComponent(const std::string& componentName);

    virtual bool SendMsg(const ActorMessage& message);
    virtual bool SendMsg(const int eventID, const std::string& data, const std::string& arg);
    virtual bool BackMsgToMainThread(const ActorMessage& message);

    virtual bool AddMessageHandler(const int nSubMsgID, ACTOR_PROCESS_FUNCTOR_PTR xBeginFunctor);

    virtual void ToMemoryCounterString(std::string& info);
protected:
	Guid id;

	IActorModule* m_pActorModule;

    Queue<ActorMessage> mMessageQueue;

	MapEx<std::string, IComponent> mComponent;

	MapEx<int, ACTOR_PROCESS_FUNCTOR> mxProcessFunctor;
};
#endif