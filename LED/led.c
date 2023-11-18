#include "led.h"

GPIO_InitTypeDef GPIO_InitStructure;	// GPIO初始化结构体


//***************初始化单一LED***************
void SingleLEDInitial(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t RCC_APB2Periph)
{
	// 使能引脚时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);

	// 设置引脚初始化结构体
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

	GPIO_SetBits(GPIOx, GPIO_Pin);	// 默认输出高电平	
}


//***************切换LED状态***************
void SwitchLEDState(TLednum ledNum, TLedState ledState)
{
	switch(ledNum)
	{
		// 设置LED0
		case LED_NUM_LED0:
		{
			// 设置为LED0
			GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;
			if(ledState == LED_STATE_ON)	
			{	
				GPIO_ResetBits(LED0_GPIO_X, LED0_GPIO_PIN);
			}				
			else if(ledState == LED_STATE_OFF)	
			{
				GPIO_SetBits(LED0_GPIO_X, LED0_GPIO_PIN);
			}			
			break;
		}
		
		// 设置LED1
		case LED_NUM_LED1:
		{
			// 设置为LED1
			GPIO_InitStructure.GPIO_Pin	  = LED1_GPIO_PIN;
			if(ledState == LED_STATE_ON)
			{
				GPIO_ResetBits(LED1_GPIO_X, LED1_GPIO_PIN);
			}
			else if(ledState == LED_STATE_OFF)	
			{
				GPIO_SetBits(LED1_GPIO_X, LED1_GPIO_PIN);
			}
			
			break;
		}		
	}
}
