#include "usart.h"
#include "stdio.h"


BYTE USART_RX_BUF[USART_RX_BUF_SIZE]; // 串口发送缓冲区
BYTE USART_TX_BUF[USART_TX_BUF_SIZE]; // 串口接收缓冲区


// 初始化串口
// 在main.c中配置中断
void UsartInitial(TUSARTNum USARTnum, uint32_t uiBaudRate)
{

	// 串口初始化
	USART_InitTypeDef USART_InitStructure;	// 串口初始化配置结构体
	GPIO_InitTypeDef  GPIO_InitStructure;	// GPIO初始化配置结构体

	USART_InitStructure.USART_BaudRate	 = uiBaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		// 8位数据格式
	USART_InitStructure.USART_StopBits	 = USART_StopBits_1;		// 一个停止位 
	USART_InitStructure.USART_Parity	 = USART_Parity_No; 		// 无奇偶校检位
	USART_InitStructure.USART_Mode		 = USART_Mode_Rx | USART_Mode_Tx; // 收发模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制

	// GPIO初始化
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	switch(USARTnum)
	{
		// USART1
		case USART_NUM_1:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	// 使能串口及GPIO时钟

			// GPIO配置
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
			GPIO_Init(GPIOA, &GPIO_InitStructure);			// 初始化GPIO

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入
			GPIO_Init(GPIOA, &GPIO_InitStructure);


			// 串口配置
			USART_Init(USART1, &USART_InitStructure);		// 初始化串口		
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	// 使能串口接收
			USART_Cmd(USART1, ENABLE);						// 使能串口
			
			break;
		}
		// USART2
		case USART_NUM_2:
		{
			RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB2Periph_GPIOA, ENABLE);
			USART_Init(USART2, &USART_InitStructure);
			USART_Cmd(USART2, ENABLE);
			
			break;
		}
		//USART3
		case USART_NUM_3:
		{
			RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB2Periph_GPIOB, ENABLE);
			USART_Init(USART3, &USART_InitStructure);
			USART_Cmd(USART3, ENABLE);
			
			break;
		}
	}
	
}


// 串口输出调试数据
void DEBUGOutput(TUSARTNum USARTNum, BYTE* p_uiData)
{
	memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF)); // 初始化USART_RX_BUF
	strcpy(USART_RX_BUF, p_uiData);
	
	switch(USARTNum)
	{

		case USART_NUM_1:
		{
			USART_SendData(USART1, USART_RX_BUF);
			
			break;
		}
		case USART_NUM_2:
		{
			break;
		}
		case USART_NUM_3:
		{
			break;
		}
		
	}
}













































