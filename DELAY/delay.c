#include "delay.h"

static uint16_t g_uiSystickUs = 0;
static uint16_t g_uiSystickMs = 0;

// 延时初始化
void DelayInitial(void)
{
	// 配置 SysTick定时器
	// 时钟源设为系统时钟8分频 72Mhz/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	
//	Systick
}
