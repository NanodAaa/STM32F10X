#ifndef _TIM_H_
#define _TIM_H_

#include "stm32f10x.h"
#include "NANODA.h"
#include "board.h"


// TIM定时初值
#define TIM_10MS_PERIOD 	72
#define TIM_10MS_PRESCALER 	10000

#define TIM_500MS_PERIOD	5000
#define TIM_500MS_PRESCALER	7200





void TIM3Initial(uint16_t uiPeriod, uint16_t uiPrescaler);


#endif