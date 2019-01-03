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



int main()
{
	Led LedBlue(GPIOE, GPIO_Pin_8);
	Led LedRed(GPIOE, GPIO_Pin_9);
	Led LedOrange(GPIOE, GPIO_Pin_10);
	Led LedGreen (GPIOE, GPIO_Pin_11);
	
	Led LedBlue2(GPIOE, GPIO_Pin_12);
	Led LedRed2(GPIOE, GPIO_Pin_13);
	Led LedOrange2(GPIOE, GPIO_Pin_14);
	Led LedGreen2(GPIOE, GPIO_Pin_15);
	
	LedRed.On();
	LedBlue.On();
	LedOrange.On();
	LedGreen.On();
	
	LedRed2.Off();
	LedBlue2.Off();
	LedOrange2.Off();
	LedGreen2.Off();

	
	while(true)
	{
		LedRed.Toggle();
		LedBlue.Toggle();
		LedOrange.Toggle();
		LedGreen.Toggle();
		
		LedRed2.Toggle();
		LedBlue2.Toggle();
		LedOrange2.Toggle();
		LedGreen2.Toggle();
		
		for(int i = 0; i<= 800000; i++);
	}
}