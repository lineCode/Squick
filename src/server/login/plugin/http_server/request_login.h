

#include "squick/base/request.h"

class NFRequestLogin : public IRequest
{
public:
	std::string user;
	std::string password;

};

AJSON(NFRequestLogin, user, password)