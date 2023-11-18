#ifndef _LED_H_
#define _LED_H_

#include "stm32f10x.h"
#include "NANODA.h"
#include "board.h"

//***************LED序号***************
typedef enum _tagLedNum
{
	LED_NUM_LED0 = 0,	// LED0
	LED_NUM_LED1,		// LED1
	
}TLednum;

//***************LED状态***************
typedef enum _tagLedState
{
	LED_STATE_ON = 0,
	LED_STATE_OFF,
	
}TLedState;

void SingleLEDInitial(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, uint32_t RCC_APB2Periph);
void SwitchLEDState(TLednum ledNum, TLedState ledState);

#endif
