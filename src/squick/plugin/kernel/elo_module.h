

#ifndef SQUICK_ELO_MODULE_H
#define SQUICK_ELO_MODULE_H

#include "squick/base/elo.h"

class ELOModule
    : public IELOModule
{
public:
	ELOModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual ~ELOModule() {};

    virtual bool Init() override;
    virtual bool Shut() override;
    virtual bool Execute() override;
    virtual bool AfterInit() override;


	virtual float Probability(int ratingA, int ratingB) override;

	virtual void EloRating(int ratingA, int ratingB, bool aWin, int& resultA, int& resultB) override;

private:
	int EloK();

private:
	int K = 50;
};


#endif
