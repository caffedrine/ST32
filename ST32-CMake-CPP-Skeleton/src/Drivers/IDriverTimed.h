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
	virtual void Tick() = 0;
	
protected:

private:
};


#endif //_IDRIVERTIMED_H
