//
// Created by James on 7/02/21.
//

#ifndef NFPBGENERATOR_H
#define NFPBGENERATOR_H
#include "../generator.h"
namespace squick::tools::file_process {
class PBGenerator : public NFIGenerator
{
public:
	PBGenerator()
	{
	}

	virtual bool Generate(const std::map<std::string, ClassData *> &classData) override
	{
		//"../proto/NFRecordDefine.proto"
		return false;
	}
};
}
#endif //NFPBGENERATOR_H
