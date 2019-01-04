//
// Created by curiosul on 1/3/19.
//

#ifndef _IDRIVERCONTAINTER_H
#define _IDRIVERCONTAINTER_H

#include <stdint.h>
#include <vector>
#include <Derivative.h>

#include "IDriverTimed.h"

class TasksContainter
{
	typedef struct Task
	{
		enum class TaskStatus
		{
			RUNNING,
			SUSPENDED,
		};
		
		uint16_t id;
		uint32_t ExecutionIntervalMillis;
		uint32_t LastExecutionMillis = 0;
		bool IsCustom;
		
		void (*ptr2func)() = nullptr;
		IDriverTimed *ptr2driver = nullptr;
		
		TaskStatus status = TaskStatus::RUNNING;
		
		bool IsSuspended()
		{
			return (status == TaskStatus::SUSPENDED);
		}
		
		void Suspend()
		{
			status = TaskStatus::SUSPENDED;
		}
		
		void Resume()
		{
			status = TaskStatus::RUNNING;
		}
		
	}task_t;
	
public:
	void Tick()
	{
		for(auto it = _TasksList.begin(); it !=_TasksList.end(); ++it)
		{
			/* Ignore tasks which are paused */
			if(it.base()->IsSuspended())
				continue;
			
			if( ( it.base()->ExecutionIntervalMillis == 0) ||
				( SysTick_CurrentTicks - it.base()->LastExecutionMillis >= it.base()->ExecutionIntervalMillis)
			  )
			{
				if(it.base()->IsCustom)
				{
					assert_param( (it.base()->ptr2func != nullptr) );
					it.base()->ptr2func();
				}
				else
				{
					assert_param( (it.base()->ptr2driver != nullptr) );
					it.base()->ptr2driver->Tick();
				}
				
				it.base()->LastExecutionMillis = SysTick_CurrentTicks;
			}
		}
	}
	
	void AddDriver(IDriverTimed *ptr2driver, uint32_t TickIntervalMillis = 0)
	{
		task_t task;
		task.IsCustom = false;
		task.ExecutionIntervalMillis = TickIntervalMillis;
		task.LastExecutionMillis = 0;
		task.ptr2driver = ptr2driver;
		task.id = task_ids_counter++;
		_TasksList.emplace_back(task);
	}
	
	void AddCustom(void (*ptr2func)(), uint32_t TickIntervalMillis = 0)
	{
		task_t task;
		task.IsCustom = true;
		task.ExecutionIntervalMillis = TickIntervalMillis;
		task.LastExecutionMillis = 0;
		task.ptr2func = ptr2func;
		task.id = task_ids_counter++;
		_TasksList.emplace_back(task);
	}
	
	void Remove( void *opaque_task)
	{
		/// TODO: Implement
	}
	
	task_t *GetTaskByPtr( void (*ptr2func)() )
	{
		for(auto it = _TasksList.begin(); it !=_TasksList.end(); ++it)
		{
			if(it.base()->IsCustom && it.base()->ptr2func != nullptr)
			{
				if( it.base()->ptr2func == ptr2func )
					return it.base();
			}
		}
		return nullptr;
	}
	
	task_t *GetTaskByPtr( IDriverTimed *ptr2driver )
	{
		for(auto it = _TasksList.begin(); it !=_TasksList.end(); ++it)
		{
			if(!it.base()->IsCustom && it.base()->ptr2driver != nullptr)
			{
				if( it.base()->ptr2driver == ptr2driver )
					return it.base();
			}
		}
		return nullptr;
	}
	
private:
	uint16_t task_ids_counter = 0;
	std::vector<task_t> _TasksList;

};


#endif //_IDRIVERCONTAINTER_H
