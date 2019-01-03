//
// Created by curiosul on 1/3/19.
//

#ifndef _IDRIVERCONTAINTER_H
#define _IDRIVERCONTAINTER_H

#include <stdint.h>

class TasksContainter
{
	typedef struct Task
	{
		uint16_t id = 0;
		bool IsCustom = false;
	}task_t;
	
public:
	void Tick()
	{
	
	}
	
	void AddDriver(void *ptr2driver, uint32_t TickIntervalMillis)
	{
	
	}
	
	void AddCustom(void *ptr2func, uint32_t TickIntervalMillis)
	{
	
	}
	
	void Remove( void *opaque_task)
	{
	
	}
	
private:

};


#endif //_IDRIVERCONTAINTER_H
