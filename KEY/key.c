#include "key.h"
#include "led.h"


extern GPIO_InitTypeDef GPIO_InitStructure;	// GPIO初始化结构体
extern uint32_t g_uiCount10ms;	// 计划用于按键消抖延时



// 初始化按键
void SingleKeyInitial(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t RCC_APB2Periph, TIfIPU ifIPU)
{
	// 初始化时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);

	// 初始化引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	// 是否默认上拉输入
	if(ifIPU == IPU_TRUE)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	}
	else
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	}
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	
}


// 扫描按键
TSingleKeyState SingleKeyScan(TKeyNum keyNum, TIfIPU ifIPU)
{
	switch(keyNum)
	{
		// 按键WK UP
		case KEY_NUM_WKUP:
		{
			// 默认上拉输入
			if(ifIPU == IPU_TRUE)
			{
				if(WKUP == Bit_SET)	return SINGLE_KEYSTATE_RELEASED;	// 按键释放状态
				else if(WKUP == Bit_RESET)
				{
//					delay_ms(10);	// 消抖
					if(WKUP == Bit_RESET)
					{
						return SINGLE_KEYSTATE_PRES;	// 按键按下状态
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;	// 按键状态未知
			}

			// 默认下拉输入
			else
			{
				if(WKUP == Bit_RESET)	return SINGLE_KEYSTATE_RELEASED;
				else if(WKUP == Bit_SET)
				{
//					delay_ms(10);
					if(WKUP == Bit_SET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}
			
			break;
		}

		
		// 按键KEY0
		case KEY_NUM_KEY0:
		{
			if(ifIPU == IPU_TRUE)
			{
				if(KEY0 == Bit_SET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY0 == Bit_RESET)
				{
					//SwitchLEDState(LED_NUM_LED0, LED_STATE_ON);
//					delay_ms(10);
					if(KEY0 == Bit_RESET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}
			else
			{
				if(KEY0 == Bit_RESET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY0 == Bit_SET)
				{
//					delay_ms(10);
					if(KEY0 == Bit_SET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}		

			break;
		}

		// 按键KEY1
		case KEY_NUM_KEY1:
		{
			if(ifIPU == IPU_TRUE)
			{
				if(KEY1 == Bit_SET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY1 == Bit_RESET)
				{
//					delay_ms(10);
					if(KEY1 == Bit_RESET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}
			else
			{
				if(KEY0 == Bit_SET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY1 == Bit_SET)
				{
//					delay_ms(10);
					if(KEY1 == Bit_SET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}		

			break;
		}

		#ifdef BOARD_AUTOONOFF_STM32F103RCT6
		// 按键KEY2
		case KEY_NUM_KEY2:
		{
			if(ifIPU == IPU_TRUE)
			{
				if(KEY2 == Bit_SET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY2== Bit_RESET)
				{
//					delay_ms(10);
					if(KEY2 == Bit_RESET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}
			else
			{
				if(KEY2 == Bit_RESET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY2 == Bit_SET)
				{
//					delay_ms(10);
					if(KEY2 == Bit_SET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}		

			break;
		}

		// 按键KEY3
		case KEY_NUM_KEY3:
		{
			if(ifIPU == IPU_TRUE)
			{
				if(KEY3 == Bit_SET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY3 == Bit_RESET)
				{
//					delay_ms(10);
					if(KEY3 == Bit_RESET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}
			else
			{
				if(KEY3 == Bit_RESET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY3 == Bit_SET)
				{
//					delay_ms(10);
					if(KEY3 == Bit_SET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}		

			break;
		}

		// 按键KEY4
		case KEY_NUM_KEY4:
		{
			if(ifIPU == IPU_TRUE)
			{
				if(KEY4 == Bit_SET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY4 == Bit_RESET)
				{
//					delay_ms(10);
					if(KEY4 == Bit_RESET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}
			else
			{
				if(KEY4 == Bit_RESET)	return SINGLE_KEYSTATE_RELEASED;
				else if(KEY4 == Bit_SET)
				{
//					delay_ms(10);
					if(KEY4 == Bit_SET)
					{
						return SINGLE_KEYSTATE_PRES;
					}
				}
				else	return SINGLE_KEYSTATE_UNKNOWN;
			}		
			
			break;
		}
		#endif
		
	}

	return SINGLE_KEYSTATE_UNKNOWN;
	
}


// 全局按键扫描
TGeneralKeyState GenKeyScan(void)
{
	// KEY0
	if(SINGLE_KEYSTATE_PRES == SingleKeyScan(KEY_NUM_KEY0, IPU_TRUE))
	{
		return GENERAL_KEYSTATE_KEY0_PRES;
	}
	// KEY1
	if(SINGLE_KEYSTATE_PRES == SingleKeyScan(KEY_NUM_KEY1, IPU_TRUE))
	{
		return GENERAL_KEYSTATE_KEY1_PRES;
	}
	// KEY2
	else if(SINGLE_KEYSTATE_PRES == SingleKeyScan(KEY_NUM_KEY2, IPU_TRUE))
	{
		return GENERAL_KEYSTATE_KEY2_PRES;
	}
	// KEY3
	else if(SINGLE_KEYSTATE_PRES == SingleKeyScan(KEY_NUM_KEY3, IPU_TRUE))
	{
		return GENERAL_KEYSTATE_KEY3_PRES;
	}
	// KEY4
	else if(SINGLE_KEYSTATE_PRES == SingleKeyScan(KEY_NUM_KEY4, IPU_TRUE))
	{
		return GENERAL_KEYSTATE_KEY4_PRES;
	}
	// 无按键
	else
	{
		return GENERAL_KEYSTATE_NOKEYPRES;
	}
}


// 按键消抖
void KeyDebounce(void)
{
	uint32_t uiCountCurrent;
	uiCountCurrent = g_uiCount10ms;
	while(g_uiCount10ms - uiCountCurrent > 0 && g_uiCount10ms - uiCountCurrent == 50);

}


