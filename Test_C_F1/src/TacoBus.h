//
// Created by curiosul on 1/17/19.
//

#ifndef SKELETONC_TACOBUS_H
#define SKELETONC_TACOBUS_H

#include <Derivative.h>
#include "Printf.h"

/* Global structure to save the results */
struct
{
	uint8_t 	FCT_cStatus;            // FCT status info
	uint8_t 	MAIN_cPumpStatus;
	uint16_t 	sr_u16_GlobAlrm;
	uint16_t 	sr_u16_RecAlrm;
	int16_t 	ADC_sdwVrms;
	int16_t 	sr_s16_ACurSam;
	int16_t 	sr_s16_BCurSam;
	int16_t 	RIFE_RifExt_wFlt;
	int16_t 	iamf;
	int16_t 	ibmf;
	int16_t 	vbusf;
	int16_t 	mbus;
	int16_t 	ium_off;
	int16_t 	ivm_off;
	int16_t 	Debug_Power;
	int16_t 	Temp;
} FctInfo;


/* TacoBus public functions */
void TacoBus_Init();
uint8_t TacoBus_GetFctInfo();
uint8_t TacoBus_LowVoltageFctConfigA();
uint8_t TacoBus_LowVoltageFctConfigB();
uint8_t TacoBus_SendCommand(uint8_t *data, uint8_t len);

#endif //SKELETONC_TACOBUS_H
