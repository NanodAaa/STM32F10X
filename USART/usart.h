#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"
#include "board.h"
#include "NANODA.h"


// 串口波特率
#define USART_BAUDRATE_9600		9600
#define USART_BAUDRATE_115200	115200


// 串口发送/接收缓冲区大小
#define USART_TX_BUF_SIZE 512
#define USART_RX_BUF_SIZE 512

// 串口号
typedef enum _tagUSARTNum
{
	USART_NUM_1 = 0,
	USART_NUM_2,
	USART_NUM_3,
}TUSARTNum;


void UsartInitial(TUSARTNum USARTnum, uint32_t uiBaudRate);
void DEBUGOutput(TUSARTNum USARTNum, BYTE* p_uiData);





















#endif
