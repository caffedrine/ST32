#include "derivative.h"

#include "TasksContainter.h"
#include "Led.h"

//class PushButton
//{
//	enum PushButtonState
//	{
//		DOWN = 0,
//		UP = 1
//	};
//
//public:
//	PushButton(GPIO_TypeDef *LedPortRegister, uint32_t LedPortBit) : _PortRegister(LedPortRegister), _PortBit(LedPortBit)
//	{
//	}
//
//	PushButtonState ReadState()
//	{
//		return PushButtonState::DOWN;
//	}
//
//	void Tick()
//	{
//
//	}
//
//protected:
//	/// TODO: Implement
//	virtual void OnStateChanged(PushButtonState NewState) {}
//private:
//	GPIO_TypeDef *_PortRegister;
//	uint32_t _PortBit;
//};

void red_task()
{
	static Led LedRed(GPIOE, GPIO_Pin_9);
	LedRed.Toggle();
}

void green_task()
{
	static Led LedGreen (GPIOE, GPIO_Pin_11);
	LedGreen.Toggle();
}

void blue_task()
{
	static Led LedBlue(GPIOE, GPIO_Pin_8);
	LedBlue.Toggle();
}

void orange_task()
{
	static Led LedOrange(GPIOE, GPIO_Pin_10);
	LedOrange.Toggle();
}

int main()
{
	SysTick_Init();
	
	Led LedBlue2(GPIOE, GPIO_Pin_12);
	Led LedRed2(GPIOE, GPIO_Pin_13);
	Led LedOrange2(GPIOE, GPIO_Pin_14);
	Led LedGreen2(GPIOE, GPIO_Pin_15);
	
	LedBlue2.Blink();
	LedRed2.Blink();
	LedOrange2.Blink();
	LedGreen2.Blink();
	
	/* Tasks scheduler drivers */
	TasksContainter tasks;
	
	/* Custom functions to be executed periodically */
	tasks.AddCustom(&red_task, 0);
	tasks.AddCustom(&green_task, 10);
	tasks.AddCustom(&blue_task, 20);
	tasks.AddCustom(&orange_task, 30);
	
	/* Driver's ticks */
	tasks.AddDriver(&LedRed2, 0);
	tasks.AddDriver(&LedGreen2, 10);
	tasks.AddDriver(&LedBlue2, 20);
	tasks.AddDriver(&LedOrange2, 30);
	
	uint32_t PrevMillis = 0;
	while(true)
	{
		if( SysTick_CurrentTicks - PrevMillis >= 1 )	/* is 1ms elapsed */
		{
			PrevMillis = SysTick_CurrentTicks;
			uint32_t start_task_millis, end_task_millis;
			start_task_millis = SysTick_CurrentTicks;
			tasks.Tick();
			end_task_millis = SysTick_CurrentTicks;
			
			if( (end_task_millis - start_task_millis) > 1 )
			{
				while(true)
				{
					int breakpoint = 0;
				}
			}
		}
	}
}