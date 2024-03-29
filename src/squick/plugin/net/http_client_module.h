
#ifndef SQUICK_HTTP_CLIENT_MODULE_H
#define SQUICK_HTTP_CLIENT_MODULE_H

#include <iostream>
#include "squick/core/map_ex.h"
#include "squick/base/kernel.h"
#include "squick/base/http_client.h"
#include "squick/base/log.h"
#include "ihttp_client.h"


class HttpClientModule
        : public IHttpClientModule
{
public:
    HttpClientModule(IPluginManager* p);

    virtual ~HttpClientModule();

	virtual bool Init();

	virtual bool AfterInit();

    virtual bool Execute();

    virtual bool Shut();

	//actually, sync post method
	//WebStatus
	virtual int Post(const std::string& strUri, const std::string& strData, std::string& strResData);
	virtual int Post(const std::string& strUri, const std::map<std::string, std::string>& xHeaders, const std::string& strData, std::string& strResData);

	//actually, sync get method
	//WebStatus
	virtual int Get(const std::string& strUri, std::string& strResData);
	virtual int Get(const std::string& strUri, const std::map<std::string, std::string>& xHeaders, std::string& strResData);
protected:
    virtual bool DoGet(const std::string& strUri,
                            const std::map<std::string, std::string>& xHeaders,
                            HTTP_RESP_FUNCTOR_PTR pCB);

    virtual bool DoPost(const std::string& strUri,
        const std::map<std::string, std::string>& xHeaders,
        const std::string& strPostData,
        HTTP_RESP_FUNCTOR_PTR pCB, const std::string& strMemo = "");


protected:

	class RespData
	{
	public:
		RespData()
		{
			resp = false;
			time = 0;
			state_code = 0;
		}

		bool resp;
		int time;
		int state_code;
		std::string strRespData;
	};

	void CallBack(const Guid id, const int state_code, const std::string& strRespData);

private:
	IKernelModule* m_pKernelModule;
	IHttpClient* m_pHttpClient;
    std::map<std::string, std::string> m_xDefaultHttpHeaders;
	MapEx<Guid, RespData> mxRespDataMap;
};

#endif
