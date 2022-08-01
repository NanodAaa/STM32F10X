#ifndef _BEEP_H_
#define _BEEP_H_


#include "stm32f10x.h"
#include "board.h"
#include "NANODA.h"


// 是否使能蜂鸣器
typedef enum _tagIfBeepEnable
{
	BEEP_ENABLE = 0,
	BEEP_UNABLE,
}TIfBeepEnable;


// 是否为NPN三极管驱动
typedef enum  _tagIfNPN
{
	NPN_TRUE = 0,
	NPN_FALSE,
}TIfNPN;


void BeepInitial(TIfNPN ifNPN);
void BeepBeep(TIfBeepEnable ifBeep, TIfNPN ifNPN);



#endif
