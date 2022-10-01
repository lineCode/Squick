

#pragma once

#include "squick/base/response.h"

class ResponseLogin : public IResponse
{
public:
	std::string jwt;

};

AJSON(ResponseLogin, jwt, code, message)