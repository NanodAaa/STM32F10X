#ifndef _DAC_H_
#define _DAC_H_

#include "stm32f10x.h"
#include "board.h"
#include "NANODA.h"

#define ALIGN_8B_DEV 	256		// 8位数据大小
#define ALIGN_12B_DEV	4096	// 12位数据大小

// 模拟电压值
#ifdef BOARD_ALIENTEK_STM32F103ZE
#define DAC_VDDA_VAL 3.3	// VRef+模拟电压参考值
#endif

void DacInitial(uint32_t DAC_Channel, uint32_t DAC_Align);
void DacSetOutputVal(uint32_t DAC_Channel, uint32_t DAC_Align, uint16_t uiDacTargetVal);

#endif
