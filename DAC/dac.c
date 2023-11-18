#include "dac.h"

// DAC初始化
// DAC_Channel -- 初始化的通道号
// DAC_Align -- 数据对齐模式
void DacInitial(uint32_t DAC_Channel, uint32_t DAC_Align)
{
	GPIO_InitTypeDef GPIO_InitStructure;	// GPIO配置
	DAC_InitTypeDef  DAC_InitStructure;		// DAC配置

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);			// 使能DAC时钟

	// 无触发
	// 不使用波形发生
	// 
	// 不使用输出缓存
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel, &DAC_InitStructure);

	// 使能DAC_OUT
	// 配置GPIO
	if(DAC_Channel == DAC_Channel_1)
	{
		RCC_APB2PeriphClockCmd(DAC_OUT1_RCC_APB2PERIPH, ENABLE);	// 使能DAC_OUT1时钟（GPIOA）
		
		GPIO_InitStructure.GPIO_Pin = DAC_OUT1_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// DAC_OUT1模拟输入
		GPIO_Init(DAC_OUT1_GPIO_X, &GPIO_InitStructure);

		DAC_Cmd(DAC_Channel, ENABLE);	// 使能DAC通道

		DAC_SetChannel1Data(DAC_Align, 0);	// 初始化DAC输出
	}
	else if(DAC_Channel == DAC_Channel_2)
	{
		RCC_APB2PeriphClockCmd(DAC_OUT2_RCC_APB2PERIPH, ENABLE);	// 使能DAC_OUT2时钟（GPIOA）
		
		GPIO_InitStructure.GPIO_Pin = DAC_OUT2_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// DAC_OUT2模拟输入
		GPIO_Init(DAC_OUT2_GPIO_X, &GPIO_InitStructure);

		DAC_Cmd(DAC_Channel, ENABLE);	// 使能DAC通道

		DAC_SetChannel2Data(DAC_Align, 0);	// 初始化DAC输出
	}

}


// 设置 DAC 的输出值
// DAC_Channel -- DAC通道号
// DAC_Align -- 数据对齐格式
// uiDacTargetVal -- 目标输出电压值
// uiDacVal / ALIGN_8B_DEV == uiDacTargetVal / DAC_VDDA_VAL -- 转换公式
void DacSetOutputVal(uint32_t DAC_Channel, uint32_t DAC_Align, uint16_t uiDacTargetVal)
{
	uint16_t uiDacVal;	// DAC的输入值

	// 计算DAC输出值
	if(DAC_Align == DAC_Align_8b_R)
		uiDacVal = ((uiDacTargetVal / DAC_VDDA_VAL) * ALIGN_8B_DEV);
	else if(DAC_Align_12b_L || DAC_Align_12b_R)
		uiDacVal = ((uiDacTargetVal / DAC_VDDA_VAL) * ALIGN_12B_DEV);

	if(DAC_Channel == DAC_Channel_1)
		DAC_SetChannel1Data(DAC_Align, uiDacVal);	// 设置DAC输出值
	else if(DAC_Channel == DAC_Channel_2)
		DAC_SetChannel2Data(DAC_Align, uiDacVal);

}
