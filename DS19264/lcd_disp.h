//			lcd_disp.h
	
#ifndef _LCD_DISP_H_
#define _LCD_DISP_H_

#include "stm32f10x.h"
#include "board.h"
#include "NANODA.h"
#include "ds19264.h"

#define CHINESE_BUF_SIZE 		50	// 汉字储存缓冲区大小
#define CHINESE_CHARA_SIZE		32	// 每个汉字的大小
#define CHINESE_LINE_CONSTANT	2	// 中文行间距常量
#define CHINESE_ROW_CONSTANT	16	// 中文列间距常量

#define BMP_BUF_SIZE		96	// 图片储存缓冲区大小
#define BMP_CHARA_SIZE		16	// 每个区块大小
#define BMP_LINE_SIZE 		8	// 图片每行的大小
#define SCREEN_NUMBER 		3	// 屏幕数量

#define DIGIT_BUF_SIZE		30	// 数字储存缓冲区大小
#define DIGIT_CHARA_SIZE	16	// 每个数字大小
#define DIGIT_LINE_CONSTANT	2	// 数字行间距常量
#define DIGIT_ROW_CONSTANT	8	// 数字列间距常量

void Ds19264WriteChar(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel, BYTE byChar);
void Ds19264WriteString(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel, BYTE* byString);
void Ds19264WriteChinese(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel, UINT byChineseBuf);
void Ds19264WriteDigit(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel, UINT byDigitBuf);
void Ds19264DisplayBMP(BYTE* byBMP);
BYTE Ds19264ReadData(TDs19264ScrnSel ds19264ScrnSel);

#endif
