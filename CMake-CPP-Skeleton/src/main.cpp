#include <Derivative.h>
#include <SysTick.h>

#include "TasksContainter.h"
#include "Drivers/LED/Led.h"
#include "Drivers/PushButton/PushButton.h"

/* Tasks scheduler drivers */
TasksContainter *tasks;
/* Global pointers to all board leds */
Led *LedOrange 	= nullptr, *LedRed 	= nullptr, *LedBlue  = nullptr, *LedGreen  = nullptr;
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
		LedOrange->On();
	}
	else if (Newstate == PushButtonState::UP)
	{
		LedOrange->Blink();
		tasks->GetTaskByPtr(&orange_task)->Resume();
	}
}

void create_instances()
{
	tasks = new TasksContainter();
	
	LedRed = new Led(GPIOD, GPIO_Pin_14);
	LedGreen = new Led(GPIOD, GPIO_Pin_12);
	LedBlue = new Led(GPIOD, GPIO_Pin_15);
	LedOrange = new Led(GPIOD, GPIO_Pin_13);
	
	UserButton = new PushButton(GPIOA, GPIO_Pin_0, 500);
	UserButton->SetCallback( &onStateChanged_UserButton );
}

int main()
{
    /* Init system tick counter */
	SysTick_Init(1000);
	
	/* Create peripherals instances */
	create_instances();
	
	/* Custom functions to be executed periodically */
	tasks->AddCustom(red_task, 0);
	tasks->AddCustom(&green_task, 250);
	tasks->AddCustom(&blue_task, 500);
	tasks->AddCustom(&orange_task, 1000);

	/* Driver's ticks */
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