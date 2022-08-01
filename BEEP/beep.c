#include "beep.h"


// 初始化蜂鸣器
void BeepInitial(TIfNPN ifNPN)
{
	GPIO_InitTypeDef GPIO_InitStructure;	// 引脚初始化结构体

	// 初始化时钟
	RCC_APB2PeriphClockCmd(BUZZER_RCC_APB2PERIPH, ENABLE);

	// 初始化引脚
	GPIO_InitStructure.GPIO_Pin   = BUZZER_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUZZER_GPIO_X, &GPIO_InitStructure);

	// NPN驱动则默认输出低电平
	// PNP驱动则默认输出高电平
	if(ifNPN == NPN_TRUE)			GPIO_ResetBits(BUZZER_GPIO_X, BUZZER_GPIO_PIN);
	else if (ifNPN == NPN_FALSE)	GPIO_SetBits(BUZZER_GPIO_X, BUZZER_GPIO_PIN);	
}


// 蜂鸣器发声
void BeepBeep(TIfBeepEnable ifBeep, TIfNPN ifNPN)
{
	if(ifBeep == BEEP_ENABLE)
	{
		// NPN驱动
		if(ifNPN == NPN_TRUE)	GPIO_SetBits(BUZZER_GPIO_X, BUZZER_GPIO_PIN);
		else	GPIO_ResetBits(BUZZER_GPIO_X, BUZZER_GPIO_PIN);
	}
	else if(ifBeep == BEEP_UNABLE)
	{
		if(ifNPN == NPN_TRUE)	GPIO_ResetBits(BUZZER_GPIO_X, BUZZER_GPIO_PIN);
		else	GPIO_SetBits(BUZZER_GPIO_X, BUZZER_GPIO_PIN);
	}
}








