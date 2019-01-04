#include <Extensions.h>
#include <Derivative.h>

#include "TasksContainter.h"
#include "Led.h"

/* Global pointers to all board leds */
Led *LedOrange 	= nullptr, *LedRed 	= nullptr, *LedBlue  = nullptr, *LedGreen  = nullptr;
Led *LedOrange2 = nullptr, *LedRed2 = nullptr, *LedBlue2 = nullptr, *LedGreen2 = nullptr;

void red_task()
{
	if(LedRed != nullptr)
		LedRed->Toggle();
}

void green_task()
{
	if(LedGreen != nullptr)
		LedGreen->Toggle();
}

void blue_task()
{
	if(LedBlue != nullptr)
		LedBlue->Toggle();
}

void orange_task()
{
	if(LedOrange != nullptr)
		LedOrange->Toggle();
}


void create_instances()
{
	LedRed = new Led(GPIOE, GPIO_Pin_9);
	LedGreen = new Led(GPIOE, GPIO_Pin_11);
	LedBlue = new Led(GPIOE, GPIO_Pin_8);
	LedOrange = new Led(GPIOE, GPIO_Pin_10);
	
	LedBlue2 = new Led(GPIOE, GPIO_Pin_12);
	LedRed2 = new Led (GPIOE, GPIO_Pin_13);
	LedOrange2 = new Led(GPIOE, GPIO_Pin_14);
	LedGreen2 = new Led(GPIOE, GPIO_Pin_15);
}

int main()
{
	SysTick_Init();
	
	/* Create peripherals instances */
	create_instances();
	
	LedBlue2->Blink();
	LedRed2->Blink();
	LedOrange2->Blink();
	LedGreen2->Blink();

	/* Tasks scheduler drivers */
	TasksContainter tasks;

	/* Custom functions to be executed periodically */
	tasks.AddCustom(&red_task, 0);
	tasks.AddCustom(&green_task, 100);
	tasks.AddCustom(&blue_task, 200);
	tasks.AddCustom(&orange_task, 300);

	/* Driver's ticks */
	tasks.AddDriver(LedRed2, 0);
	tasks.AddDriver(LedGreen2, 100);
	tasks.AddDriver(LedBlue2, 200);
	tasks.AddDriver(LedOrange2, 300);

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
					;
				}
			}
		}
	}
}