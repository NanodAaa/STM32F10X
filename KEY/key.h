#ifndef _KEY_H_
#define _KEY_H_

#include "NANODA.h"
#include "board.h"
#include "stm32f10x.h"
#include "delay.h"

// 按键输入引脚定义
#define WKUP GPIO_ReadInputDataBit(WKUP_GPIO_X, WKUP_GPIO_PIN)
#define KEY0 GPIO_ReadInputDataBit(KEY0_GPIO_X, KEY0_GPIO_PIN)
#define KEY1 GPIO_ReadInputDataBit(KEY1_GPIO_X, KEY1_GPIO_PIN)
#define KEY2 GPIO_ReadInputDataBit(KEY2_GPIO_X, KEY2_GPIO_PIN)
#define KEY3 GPIO_ReadInputDataBit(KEY3_GPIO_X, KEY3_GPIO_PIN)
#define KEY4 GPIO_ReadInputDataBit(KEY4_GPIO_X, KEY4_GPIO_PIN)

// 按键序号
typedef enum _tagKeyNum
{
	KEY_NUM_WKUP = 0,		   // 唤醒按键
	KEY_NUM_KEY0,			   // 按键0
	KEY_NUM_KEY1,			   // 按键1
	KEY_NUM_KEY2,			   // 按键2
	KEY_NUM_KEY3,			   // 按键3
	KEY_NUM_KEY4,			   // 按键4
}TKeyNum;

// 单一按键状态
typedef enum _tagSingleKeyState
{
	SINGLE_KEYSTATE_UNKNOWN = 0,		// 未知状态
	SINGLE_KEYSTATE_RELEASED,			// 释放状态
	SINGLE_KEYSTATE_PRES,				// 按下状态
}TSingleKeyState;

// 是否默认上拉
typedef enum _tagIfIPU
{
	IPU_TRUE = 0,
	IPU_FALSE,
}TIfIPU;


// 全局按键状态
typedef enum _tagGeneralKeyState
{
	GENERAL_KEYSTATE_KEYWKUP_PRES = 0,	// 唤醒按键按下
	GENERAL_KEYSTATE_KEY0_PRES,			// KEY0按下
	GENERAL_KEYSTATE_KEY1_PRES,			// KEY1按下
	GENERAL_KEYSTATE_KEY2_PRES,			// KEY2按下
	GENERAL_KEYSTATE_KEY3_PRES,			// KEY3按下
	GENERAL_KEYSTATE_KEY4_PRES,			// KEY4按下
	GENERAL_KEYSTATE_NOKEYPRES			// 无按键按下
}TGeneralKeyState;

void SingleKeyInitial(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, uint32_t RCC_APB2Periph, TIfIPU ifIPU);
TSingleKeyState SingleKeyScan(TKeyNum keyNum, TIfIPU ifIPU);
TGeneralKeyState GenKeyScan(void);
void KeyDebounce(void);

#endif
