
#pragma once

#include "squick/base/request.h"

class RequestSelectWorld : public IRequest
{
public:
	int id;

};

AJSON(RequestSelectWorld, id)