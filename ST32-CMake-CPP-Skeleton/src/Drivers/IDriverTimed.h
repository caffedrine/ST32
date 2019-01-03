//
// Created by curiosul on 1/3/19.
//

#ifndef _IDRIVERTIMED_H
#define _IDRIVERTIMED_H

#include "derivative.h"
#include "IDriver.h"

class IDriverTimed
{
public:
	void ExecuteTasks()
	{
	
	}
	
	void AddDriver(uint32_t TickPeriodMillis)
	{
	
	}
	
	void RemoveDriver()
	{
	
	}
	
	
protected:
	virtual void Tick() = 0;
private:
};


#endif //_IDRIVERTIMED_H
