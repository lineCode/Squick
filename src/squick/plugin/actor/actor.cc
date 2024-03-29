

#include "actor.h"
#include "squick/base/plugin_manager.h"

Actor::Actor(const Guid id, IActorModule* pModule)
{
	this->id = id;
	m_pActorModule = pModule;
}

Actor::~Actor()
{
}

const Guid Actor::ID()
{
	return this->id;
}

bool Actor::Execute()
{
	//bulk
	ActorMessage messageObject;
	while (mMessageQueue.TryPop(messageObject))
	{
		//must make sure that only one thread running this function at the same time
		//mxProcessFunctor is not thread-safe
		ACTOR_PROCESS_FUNCTOR_PTR xBeginFunctor = mxProcessFunctor.GetElement(messageObject.msgID);

		if (xBeginFunctor != nullptr)
		{
			//std::cout << ID().ToString() << " received message " << messageObject.msgID << " and msg index is " << messageObject.index << " totaly msg count: " << mMessageQueue.size_approx() << std::endl;

			xBeginFunctor->operator()(messageObject);

			//return the result to the main thread
			m_pActorModule->AddResult(messageObject);
		}
	}

	return true;
}

bool Actor::AddComponent(SQUICK_SHARE_PTR<IComponent> component)
{
	//if you want to add more components for the actor, please don't clear the component
	//mComponent.ClearAll();
	if (!mComponent.ExistElement(component->GetComponentName()))
	{
		mComponent.AddElement(component->GetComponentName(), component);
		component->SetActor(SQUICK_SHARE_PTR<IActor>(this));

		component->Awake();
		component->Init();
		component->AfterInit();
		component->ReadyExecute();

		return true;
	}

	return false;
}

bool Actor::RemoveComponent(const std::string& componentName)
{
	return false;
}

SQUICK_SHARE_PTR<IComponent> Actor::FindComponent(const std::string & componentName)
{
	return mComponent.GetElement(componentName);
}

bool Actor::AddMessageHandler(const int nSubMsgID, ACTOR_PROCESS_FUNCTOR_PTR xBeginFunctor)
{
	return mxProcessFunctor.AddElement(nSubMsgID, xBeginFunctor);
}

bool Actor::SendMsg(const ActorMessage& message)
{
	return mMessageQueue.Push(message);
}

bool Actor::SendMsg(const int eventID, const std::string& data, const std::string& arg)
{
	static ActorMessage xMessage;

	xMessage.id = this->id;
	xMessage.msgID = eventID;
	xMessage.data = data;
	xMessage.arg = arg;

	return SendMsg(xMessage);
}

bool Actor::BackMsgToMainThread(const ActorMessage& message)
{
	return m_pActorModule->AddResult(message);
}

void Actor::ToMemoryCounterString(std::string& info)
{
	info.append(id.ToString());
	info.append(":Actor:");
	info.append(std::to_string(mMessageQueue.size_approx()));
}