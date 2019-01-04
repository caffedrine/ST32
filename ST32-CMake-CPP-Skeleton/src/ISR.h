
#ifndef _ISR_H
#define _ISR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <Derivative.h>

//void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/* Systick */
extern volatile uint32_t SysTick_CurrentTicks;

#ifdef __cplusplus
}
#endif

#endif /* _ISR_H */
