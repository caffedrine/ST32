#include <Derivative.h>
#include <SysTick.h>

#include "TasksContainter.h"
#include "Drivers/LED/Led.h"
#include "Drivers/PushButton/PushButton.h"

/* Tasks scheduler drivers */
TasksContainter *tasks;
/* Global pointers to all board leds */
Led *LedOrange 	= nullptr, *LedRed 	= nullptr, *LedBlue  = nullptr, *LedGreen  = nullptr;
Led *LedOrange2 = nullptr, *LedRed2 = nullptr, *LedBlue2 = nullptr, *LedGreen2 = nullptr;
PushButton *UserButton = nullptr;

void red_task()
{
		LedRed->Toggle();
}

void green_task()
{
		LedGreen->Toggle();
}

void blue_task()
{
		LedBlue->Toggle();
}

void orange_task()
{
		LedOrange->Toggle();
}

void onStateChanged_UserButton(PushButtonState Newstate)
{
	if(Newstate == PushButtonState::DOWN)
	{
		tasks->GetTaskByPtr(&orange_task)->Suspend();
		tasks->GetTaskByPtr(LedOrange2)->Suspend();
		
		LedOrange->On();
		LedOrange2->On();
	}
	else if (Newstate == PushButtonState::UP)
	{
		LedOrange->Blink();
		LedOrange2->Blink();
		
		tasks->GetTaskByPtr(&orange_task)->Resume();
		tasks->GetTaskByPtr(LedOrange2)->Resume();
	}
}

void create_instances()
{
	tasks = new TasksContainter();
	
	LedRed = new Led(GPIOE, GPIO_Pin_9);
	LedGreen = new Led(GPIOE, GPIO_Pin_11);
	LedBlue = new Led(GPIOE, GPIO_Pin_8);
	LedOrange = new Led(GPIOE, GPIO_Pin_10);
	
	LedBlue2 = new Led(GPIOE, GPIO_Pin_12);
	LedRed2 = new Led (GPIOE, GPIO_Pin_13);
	LedOrange2 = new Led(GPIOE, GPIO_Pin_14);
	LedGreen2 = new Led(GPIOE, GPIO_Pin_15);
	
	UserButton = new PushButton(GPIOA, GPIO_Pin_0, 500);
	UserButton->SetCallback( &onStateChanged_UserButton );
}

int main()
{
	SysTick_Init(1000);
	
	/* Create peripherals instances */
	create_instances();
	
	LedBlue2->Blink();
	LedRed2->Blink();
	LedOrange2->Blink();
	LedGreen2->Blink();
	
	/* Custom functions to be executed periodically */
	tasks->AddCustom(&red_task, 0);
	tasks->AddCustom(&green_task, 100);
	tasks->AddCustom(&blue_task, 200);
	tasks->AddCustom(&orange_task, 300);

	/* Driver's ticks */
	tasks->AddDriver(LedRed2, 0);
	tasks->AddDriver(LedGreen2, 100);
	tasks->AddDriver(LedBlue2, 200);
	tasks->AddDriver(LedOrange2, 300);
	tasks->AddDriver(UserButton, 10);
	
	uint32_t PrevMillis = 0;
	while(true)
	{
		if( g_SysTick_CurrentTicks - PrevMillis >= 1 )	/* is 1ms elapsed */
		{
			PrevMillis = g_SysTick_CurrentTicks;
			uint32_t start_task_millis, end_task_millis;
			start_task_millis = g_SysTick_CurrentTicks;
			{
				tasks->Tick();
			}
			end_task_millis = g_SysTick_CurrentTicks;

			if( (end_task_millis - start_task_millis) > 1 )
			{
				while(true)
				{
					;
				}
			}
		}
	}/*while*/
}/*main*/