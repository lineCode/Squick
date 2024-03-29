

#ifndef SQUICK_PERFORMANCE_H
#define SQUICK_PERFORMANCE_H

#include <iostream>
#include <time.h>

class Performance
{
private:
	int64_t time = 0;
	int64_t checkTime = 0;

public:
	Performance()
	{
		time = NFGetTimeMS();
	}

	bool CheckTimePoint(const int milliSecond = 1)
	{
		checkTime = NFGetTimeMS();
		if (checkTime > milliSecond + time)
		{
			return true;
		}

		return false;
	}

	int64_t TimeScope()
	{
		return NFGetTimeMS() - time;
	}
};

#endif