

#ifndef SQUICK_ERROR_BUS_MODULE_H
#define SQUICK_ERROR_BUS_MODULE_H

#include <iostream>
#include "squick/base/error_bus.h"

class ErrorBusModule
    : public IErrorBusModule
{
public:
	ErrorBusModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual ~ErrorBusModule()
    {
    }

	virtual ErrorData GetLastError();
	
	virtual void AddError(const Guid object, const ErrID err, const std::string& stData);

	virtual void ClearAllError();

private:


private:
	std::list<ErrorData> mErrList;
};

#endif