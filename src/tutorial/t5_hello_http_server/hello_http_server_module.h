

#ifndef NF_HELLO_WORLD_H
#define NF_HELLO_WORLD_H

#include <iostream>

#include "NFComm/NFCore/NFObject.h"
#include "NFComm/NFCore/DataList.hpp"
#include "NFComm/NFMessageDefine/SquickStructDefine.h"
#include "NFComm/NFPluginModule/IModule.h"
#include "NFComm/NFPluginModule/NFPlatform.h"
#include "NFComm/NFPluginModule/NFIHttpClientModule.h"
#include "NFComm/NFPluginModule/NFIHttpServerModule.h"
#include "NFComm/NFPluginModule/NFIWSModule.h"
#include "NFComm/NFPluginModule/IPlugin.h"
#include "NFComm/NFPluginModule/IPluginManager.h"
#include "NFComm/NFPluginModule/NFIClassModule.h"
#include "NFComm/NFPluginModule/NFIElementModule.h"
#include "NFComm/NFPluginModule/NFIScheduleModule.h"
#include "NFComm/NFPluginModule/NFINetModule.h"

/*
IN THIS PLUGIN:
YOU WILL KNOW HOW TO USE THE "NFIHttpServerModule" AND "NFIHttpClientModule" TO PROCESS WEB SERVICES AND ACCESS WEB RESOURCES
*/

class NFIHelloWorld5
	: public IModule
{

};

class NFHelloWorld5
    : public NFIHelloWorld5
{
public:
    NFHelloWorld5(IPluginManager* p)
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
	bool OnCommandQuery(NF_SHARE_PTR<NFHttpRequest> req);

	NFWebStatus OnFilter(NF_SHARE_PTR<NFHttpRequest> req);

	int OnHeartBeat(const Guid& self, const std::string& heartBeat, const float time, const int count);

	void OnGetCallBack(const Guid id, const int state_code, const std::string& strRespData);
	void OnPostCallBack(const Guid id, const int state_code, const std::string& strRespData, const std::string& strMemoData);

    void OnWebSocketTestProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

	void OnTCPEvent(const NFSOCK fd, const NF_NET_EVENT event, NFINet* pNet);

	void OnLoginProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

private:

	NFIClassModule* m_pLogicClassModule;
	NFIHttpServerModule* m_pHttpNetModule;
	NFIHttpClientModule* m_pHttpClientModule;
	NFIWSModule* m_pWSModule;
	NFIElementModule* m_pElementModule;
	NFIScheduleModule* m_pScheduleModule;
	NFINetModule* m_pNetModule;
};

#endif
