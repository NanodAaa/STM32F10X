#include "TIM.h"
#include "LED.h"


// 初始化TIM3定时器
// uiPeriod——自动重装值
// uiPrescaler——时钟预分频数
void TIM3Initial(uint16_t uiPeriod, uint16_t uiPrescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	// 定时器初始化结构体

	// 使能引脚时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// 初始化定时器参数
	TIM_TimeBaseStructure.TIM_Prescaler 	= uiPrescaler - 1;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period 		= uiPeriod - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	// 允许更新中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	// 使能TIM3
	TIM_Cmd(TIM3, ENABLE);
	
}



































