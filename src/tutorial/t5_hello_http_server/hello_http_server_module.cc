
#include "HelloWorld5.h"


bool NFHelloWorld5::Init()
{ 
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pScheduleModule = pPluginManager->FindModule<NFIScheduleModule>();
	m_pLogicClassModule = pPluginManager->FindModule<NFIClassModule>();
	m_pHttpClientModule = pPluginManager->FindModule<NFIHttpClientModule>();
	m_pHttpNetModule = pPluginManager->FindModule<NFIHttpServerModule>();
	m_pWSModule = pPluginManager->FindModule<NFIWSModule>();
	m_pNetModule = pPluginManager->FindModule<NFINetModule>();
	
    return true;
}

bool NFHelloWorld5::AfterInit()
{
	m_pScheduleModule->AddSchedule(Guid(0, 1), "OnHeartBeat1", this, &NFHelloWorld5::OnHeartBeat, 5.0f, 10);
	m_pScheduleModule->AddSchedule(Guid(0, 1), "OnHeartBeat2", this, &NFHelloWorld5::OnHeartBeat, 5.0f, 10);

	std::cout << "Hello, world, Init" << std::endl;
	//http://127.0.0.1/json
	m_pHttpNetModule->AddRequestHandler("/json", NFHttpType::NF_HTTP_REQ_GET, this, &NFHelloWorld5::OnCommandQuery);
	m_pHttpNetModule->AddRequestHandler("/json", NFHttpType::NF_HTTP_REQ_POST, this, &NFHelloWorld5::OnCommandQuery);
	m_pHttpNetModule->AddRequestHandler("/json", NFHttpType::NF_HTTP_REQ_DELETE, this, &NFHelloWorld5::OnCommandQuery);
	m_pHttpNetModule->AddRequestHandler("/json", NFHttpType::NF_HTTP_REQ_PUT, this, &NFHelloWorld5::OnCommandQuery);

	m_pHttpNetModule->AddNetFilter("/json", this, &NFHelloWorld5::OnFilter);

	m_pHttpNetModule->InitServer(8080);


    m_pWSModule->Initialization(9999, 8090, 4);

	m_pWSModule->AddReceiveCallBack(this, &NFHelloWorld5::OnWebSocketTestProcess);

	m_pNetModule->Initialization(9999, 5001);
	m_pNetModule->AddEventCallBack( this, &NFHelloWorld5::OnTCPEvent);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_LOGIN, this, &NFHelloWorld5::OnLoginProcess);

    return true;
}

bool NFHelloWorld5::Execute()
{
	if(m_pHttpNetModule)
		m_pHttpNetModule->Execute();
 
    return true;
}

bool NFHelloWorld5::BeforeShut()
{
    
    std::cout << "Hello, world2, BeforeShut" << std::endl;

    return true;
}

bool NFHelloWorld5::Shut()
{
    
    std::cout << "Hello, world2, Shut" << std::endl;

    return true;
}

bool NFHelloWorld5::OnCommandQuery(NF_SHARE_PTR<NFHttpRequest> req)
{
	std::cout << "url: " << req->url << std::endl;
	std::cout << "path: " << req->path << std::endl;
	std::cout << "type: " << req->type << std::endl;
	std::cout << "body: " << req->body << std::endl;

	std::cout << "params: " << std::endl;

	for (auto item : req->params)
	{
		std::cout << item.first << ":" << item.second << std::endl;
	}

	std::cout << "headers: " << std::endl;

	for (auto item : req->headers)
	{
		std::cout << item.first << ":" << item.second << std::endl;
	}

	return m_pHttpNetModule->ResponseMsg(req, "OnCommandQuery --- test1", NFWebStatus::WEB_OK);
}

NFWebStatus NFHelloWorld5::OnFilter(NF_SHARE_PTR<NFHttpRequest> req)
{
	std::cout << "OnFilter ... " << std::endl;

	return NFWebStatus::WEB_OK;
}

int NFHelloWorld5::OnHeartBeat(const Guid & self, const std::string & heartBeat, const float time, const int count)
{
	std::cout << heartBeat << std::endl;

	m_pHttpClientModule->DoGet("http://127.0.0.1:8080/json", this, &NFHelloWorld5::OnGetCallBack);
	m_pHttpClientModule->DoGet("http://127.0.0.1:8080/json", [](const Guid id, const int state_code, const std::string & strRespData, const std::string & strMemoData) -> void
	{
		std::cout << "OnGetCallBack" << std::endl;
	});

    std::string strMemo = "Memo here";
	m_pHttpClientModule->DoPost("http://127.0.0.1:8080/json", "OnHeartBeat post data---", this, &NFHelloWorld5::OnPostCallBack, strMemo);

	m_pHttpClientModule->DoPost("http://127.0.0.1:8080/json", "OnHeartBeat post data---", [](const Guid id, const int state_code, const std::string & strRespData, const std::string & strMemoData) -> void
	{
		std::cout << "OnPostCallBack" << std::endl;
	});

	return 0;
}

void NFHelloWorld5::OnGetCallBack(const Guid id, const int state_code, const std::string & strRespData)
{
	std::cout << "OnGetCallBack" << std::endl;
}

void NFHelloWorld5::OnPostCallBack(const Guid id, const int state_code, const std::string& strRespData, const std::string& strMemoData)
{
    std::cout << "OnPostCallBack" << " "<< strMemoData <<std::endl;
}

///////////////////////////////////////web socket ////////////////////////////////////////

void NFHelloWorld5::OnWebSocketTestProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	std::string s(msg, len);
    std::cout << s << std::endl;
    m_pWSModule->SendMsg(s, sockIndex);
}

void NFHelloWorld5::OnTCPEvent(const NFSOCK fd, const NF_NET_EVENT event, NFINet * pNet)
{
	std::cout << "fd:" << fd << " event " << event << std::endl;
}

void NFHelloWorld5::OnLoginProcess(const NFSOCK sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	Guid nPlayerID;
	SquickStruct::ReqAccountLogin xMsg;
	if (!m_pNetModule->ReceivePB(msgID, msg, len, xMsg, nPlayerID))
	{
		return;
	}

	std::cout << xMsg.account() << " " << xMsg.password() << std::endl;
}
