#include "squick/base/module.h"

class ILoginLogicModule
    : public IModule
{
public:
    virtual void OnLoginProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len) = 0;

};