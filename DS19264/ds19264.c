#include "ds19264.h"


// 初始化DS19264
void Ds19264Initial(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	// GPIO初始化结构体

	// 初始化时钟
	RCC_APB2PeriphClockCmd(LCDDB0_RCC_APB2PERIPH | LCDRS_RCC_APB2PERIPH | LCDCS1_RCC_APB2PERIPH, ENABLE);

	// 初始化GPIO
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = LCDDB0_GPIO_PIN;
	GPIO_Init(LCDDB0_GPIO_X, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LCDDB1_GPIO_PIN;
	GPIO_Init(LCDDB1_GPIO_X, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LCDDB2_GPIO_PIN;
	GPIO_Init(LCDDB2_GPIO_X, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LCDDB3_GPIO_PIN;
	GPIO_Init(LCDDB3_GPIO_X, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LCDDB4_GPIO_PIN;
	GPIO_Init(LCDDB4_GPIO_X, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LCDDB5_GPIO_PIN;
	GPIO_Init(LCDDB5_GPIO_X, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LCDDB6_GPIO_PIN;
	GPIO_Init(LCDDB6_GPIO_X, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LCDDB7_GPIO_PIN;
	GPIO_Init(LCDDB7_GPIO_X, &GPIO_InitStructure);
	
	GPIO_SetBits(LCDCS1_GPIO_X, LCDCS1_GPIO_PIN);	// CS1初始为1
	GPIO_InitStructure.GPIO_Pin = LCDCS1_GPIO_PIN;
	GPIO_Init(LCDCS1_GPIO_X, &GPIO_InitStructure);

	
	GPIO_InitStructure.GPIO_Pin = LCDCS2_GPIO_PIN;
	GPIO_Init(LCDCS2_GPIO_X, &GPIO_InitStructure);
	GPIO_SetBits(LCDCS2_GPIO_X, LCDCS2_GPIO_PIN);	// CS2初始为1
	
	GPIO_InitStructure.GPIO_Pin = LCDCS3_GPIO_PIN;
	GPIO_Init(LCDCS3_GPIO_X, &GPIO_InitStructure);
	GPIO_SetBits(LCDCS3_GPIO_X, LCDCS3_GPIO_PIN); 	// CS3初始为1
	
	GPIO_InitStructure.GPIO_Pin = LCDRS_GPIO_PIN;
	GPIO_Init(LCDRS_GPIO_X, &GPIO_InitStructure);
	GPIO_ResetBits(LCDRS_GPIO_X, LCDRS_GPIO_PIN);	// RS初始为0
	
	GPIO_InitStructure.GPIO_Pin = LCDRW_GPIO_PIN;
	GPIO_Init(LCDRW_GPIO_X, &GPIO_InitStructure);
	GPIO_ResetBits(LCDRW_GPIO_X, LCDRW_GPIO_PIN);	// RW初始为0
	
	GPIO_InitStructure.GPIO_Pin = LCDEN_GPIO_PIN;
	GPIO_Init(LCDEN_GPIO_X, &GPIO_InitStructure);
	GPIO_ResetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);	// EN初始为0
		
	DS19264_ALL_SCREEN_ON	// 开启所有屏幕
	
	DS19264_ALL_SCREEN_START_0	// 所有屏幕显示起始位置设置为0
	
//	DS19264WriteCmd(SCREEN_OFF, LEFT_SCRN);	// 屏幕关显示*

	// 所有屏幕开启后才进行下一步
	while( DS19264_NOW_ON != Ds19264ReadStatus(STATUS_CHECK_ONOFF, LEFT_SCRN)
		&& DS19264_NOW_ON != Ds19264ReadStatus(STATUS_CHECK_ONOFF, MID_SCRN)
		&& DS19264_NOW_ON != Ds19264ReadStatus(STATUS_CHECK_ONOFF, RIGHT_SCRN));	

	// 所有屏幕为正常工作状态才进行下一步
	while( DS19264_NOW_NORMAL != Ds19264ReadStatus(STATUS_CHECK_RESET, LEFT_SCRN)
		&& DS19264_NOW_NORMAL != Ds19264ReadStatus(STATUS_CHECK_RESET, MID_SCRN)
		&& DS19264_NOW_NORMAL != Ds19264ReadStatus(STATUS_CHECK_RESET, RIGHT_SCRN));

	DS19264_ALL_SCREEN_CLEAN	// 清屏
}


// ds19264读取状态字
TDs19264Stat Ds19264ReadStatus(TDs19264Stat ds19264Status, TDs19264ScrnSel ds19264ScrnSel)
{
	BYTE byStatus = DS19264ReadCmd(ds19264ScrnSel);	// 获取LCDDB信息

	switch(ds19264Status)
	{
		// 检测繁忙
		case STATUS_CHECK_BUSY:
			if(byStatus & LCD_STATUS_FLAG_BUSY)
				return DS19264_NOW_BUSY;
			else
				return DS19264_NOW_FREE;

 		// 检测开关
		case STATUS_CHECK_ONOFF:
			if(byStatus & LCD_STATUS_FLAG_ON_OFF)
				return DS19264_NOW_OFF;
			else
				return DS19264_NOW_ON;

		// 检测复位工作状态
		case STATUS_CHECK_RESET:
			if(byStatus & LCD_STATUS_FLAG_RESETING)
				return DS19264_NOW_RESET;
			else
				return DS19264_NOW_NORMAL;
	}
	return DS19264_NOW_NORMAL;
}


// ds19264 ReadCmd
BYTE DS19264ReadCmd(TDs19264ScrnSel ds19264ScrnSel)
{
	GPIO_InitTypeDef GPIO_InitStructure;	// GPIO配置结构体
	BYTE byTemp;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		// 模式设置为上拉输入，读取LCD引脚电平
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = 0xFF; 			//DB7..DB0
		GPIO_Init(LCDDB7_GPIO_X, &GPIO_InitStructure);

	Ds19264CSCtrl(ds19264ScrnSel);	// CS1/CS2/CS3 = 0
	
	GPIO_ResetBits(LCDRS_GPIO_X, LCDRS_GPIO_PIN);	// RS = 0
	GPIO_SetBits(LCDRW_GPIO_X, LCDRW_GPIO_PIN);		// RW = 1
	
	// EN = 1
	GPIO_SetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);

	byTemp = (GPIO_ReadInputData(LCDDB0_GPIO_X) & 0x00FF);	// 读取LCDDB

	GPIO_ResetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);	// EN = 0
	GPIO_ResetBits(LCDRS_GPIO_X, LCDRS_GPIO_PIN);	// RS = 0

	LCD_CS_DESELECT_ALL	// 取消所有片选

	return byTemp;
	
}


// Ds19264读取显示数据
// ds19264ScrnSel -- 屏幕选择
BYTE Ds19264ReadData(TDs19264ScrnSel ds19264ScrnSel)
{
	GPIO_InitTypeDef GPIO_InitStructure;	// GPIO配置结构体
	BYTE byDisplayData;

	while(DS19264_NOW_BUSY == Ds19264ReadStatus(STATUS_CHECK_BUSY, ds19264ScrnSel));	// 检测繁忙

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		// 模式设置为上拉输入，读取LCD引脚电平
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = 0xFF; 			//DB7..DB0
		GPIO_Init(LCDDB7_GPIO_X, &GPIO_InitStructure);			

	Ds19264CSCtrl(ds19264ScrnSel); // CS1/CS2/CS3 = 0
	
	GPIO_SetBits(LCDRS_GPIO_X, LCDRS_GPIO_PIN);		// RS = 1
	GPIO_SetBits(LCDRW_GPIO_X, LCDRW_GPIO_PIN);		// RW = 1
	GPIO_SetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);		// EN = 1

	byDisplayData = (GPIO_ReadInputData(LCDDB0_GPIO_X) & 0x00FF);	// 读取LCDDB

	GPIO_ResetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);	// EN = 0

	LCD_CS_DESELECT_ALL	// 取消所有片选

	return byDisplayData;
	
}


// Ds19264读取字符
// uiDispLine -- 显示行设置（X），取值范围 0 ~ 7H
// uiDispRow  -- 显示列设置（Y），取值范围 0 ~ 3FH
BYTE Ds19264ReadChar(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel)
{
	BYTE byChar;
	Ds19264DispLocationSet(uiDispLine, uiDispRow, ds19264ScrnSel);	// 设置读取地址
	byChar = Ds19264ReadData(ds19264ScrnSel);	// 读取字符
	return byChar;	
}


// 起始行设置
// ulStartLine -- 起始行设置，取值范围 0 ~ 3FH，
void Ds19264StartLineSet(UCHAR ulStartLine, TDs19264ScrnSel ds19264ScrnSel)
{
	while(DS19264_NOW_BUSY == Ds19264ReadStatus(STATUS_CHECK_BUSY, ds19264ScrnSel));	// 检测繁忙
	DS19264WriteCmd((0xc0 + ulStartLine), ds19264ScrnSel);	// 设置起始行
}


// 显示位置设置

// uiDispLine -- 显示行设置（X），取值范围 0 ~ 7H
// uiDispRow  -- 显示列设置（Y），取值范围 0 ~ 3FH
void Ds19264DispLocationSet(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel)
{
	while(DS19264_NOW_BUSY == Ds19264ReadStatus(STATUS_CHECK_BUSY, ds19264ScrnSel));
	DS19264WriteCmd((0xb8 + uiDispLine), ds19264ScrnSel);	// 设置行位置
	DS19264WriteCmd((0x40 + uiDispRow),  ds19264ScrnSel);	// 设置列位置
}


// LCD清屏
// ds19264ScrnSel -- 选择要清屏的屏幕
void Ds19264CleanScreen(TDs19264ScrnSel ds19264ScrnSel)
{
	UCHAR uiDispLineCount;	// 行地址计数
	UCHAR uiDispRowCount;	// 列地址计数

	// 向所有DDRAM中写0x00
	for(uiDispLineCount = 0; uiDispLineCount < DDRAM_DISPLINE_SIZE; uiDispLineCount++)
	{
		for(uiDispRowCount = 0; uiDispRowCount < DDRAM_DISPROW_SIZE; uiDispRowCount++)
		{
			Ds19264DispLocationSet(uiDispLineCount, uiDispRowCount, ds19264ScrnSel);	// 选择写入地址
			
			Ds19264WriteData(SCREEN_CLEAN_BYTE, ds19264ScrnSel);	// 写入清屏数据
		}
	}
}



// LCDCS控制
// ds19264ScrnSel -- 选择要控制的屏幕
void Ds19264CSCtrl(TDs19264ScrnSel ds19264ScrnSel)
{
	// CS1/CS2/CS3 = 0
	switch(ds19264ScrnSel)
	{
		case LEFT_SCRN:
		{
			GPIO_ResetBits(LCDCS1_GPIO_X, LCDCS1_GPIO_PIN);
			break;
		}				
		case MID_SCRN:
		{
			GPIO_ResetBits(LCDCS2_GPIO_X, LCDCS2_GPIO_PIN);
			break;
		}		
		case RIGHT_SCRN:
		{
			GPIO_ResetBits(LCDCS3_GPIO_X, LCDCS3_GPIO_PIN);
			break;
		}
	}
}
