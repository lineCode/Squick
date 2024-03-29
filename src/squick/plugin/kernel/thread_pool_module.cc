


#include "thread_pool_module.h"

ThreadPoolModule::ThreadPoolModule(IPluginManager* p)
{
    m_bIsExecute = true;
	pPluginManager = p;
}

ThreadPoolModule::~ThreadPoolModule()
{
}

bool ThreadPoolModule::Init()
{
	for (int i = 0; i < pPluginManager->GetAppCPUCount(); ++i)
	{
		mThreadPool.push_back(SQUICK_SHARE_PTR<ThreadCell>(SQUICK_NEW ThreadCell(this)));
	}

    return true;
}

bool ThreadPoolModule::AfterInit()
{

    return true;
}

bool ThreadPoolModule::BeforeShut()
{
    return true;
}

bool ThreadPoolModule::Shut()
{
 
    return true;
}

bool ThreadPoolModule::Execute()
{
	ExecuteTaskResult();

    return true;
}

void ThreadPoolModule::DoAsyncTask(const Guid taskID, const std::string & data, TASK_PROCESS_FUNCTOR asyncFunctor, TASK_PROCESS_FUNCTOR functor_end)
{
	ThreadTask task;
	task.nTaskID = taskID;
	task.data = data;
	task.xThreadFunc = asyncFunctor;
	task.xEndFunc = functor_end;
	
	size_t index = 0;
	if (!taskID.IsNull())
	{
		index = taskID.nData64 % mThreadPool.size();
	}
	
	SQUICK_SHARE_PTR<ThreadCell> threadobject = mThreadPool[index];
	threadobject->AddTask(task);
}

void ThreadPoolModule::ExecuteTaskResult()
{
	ThreadTask xMsg;
	while (mTaskResult.TryPop(xMsg))
	{
		if (xMsg.xEndFunc)
		{
			xMsg.xEndFunc.operator()(xMsg);
		}
	}
}

void ThreadPoolModule::TaskResult(const ThreadTask& task)
{
	mTaskResult.Push(task);
}

int ThreadPoolModule::GetThreadCount()
{
	return (int)mThreadPool.size();
}

