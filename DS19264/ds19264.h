#ifndef _DS19264_H_
#define _DS19264_H_


#include "stm32f10x.h"
#include "NANODA.h"
#include "board.h"
#include "delay.h"

#define LCD_CS_DESELECT_ALL		GPIO_SetBits(LCDCS1_GPIO_X, LCDCS1_GPIO_PIN); \
									GPIO_SetBits(LCDCS2_GPIO_X, LCDCS2_GPIO_PIN); \
									GPIO_SetBits(LCDCS3_GPIO_X, LCDCS3_GPIO_PIN);

 
// LCD19264-5
#ifdef BOARD_ALIENTEK_STM32F103ZE
#define LCDDB0_GPIO_X			GPIOC
#define LCDDB0_GPIO_PIN			GPIO_Pin_0
#define LCDDB0_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB1_GPIO_X			GPIOC
#define LCDDB1_GPIO_PIN			GPIO_Pin_1
#define LCDDB1_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB2_GPIO_X			GPIOC
#define LCDDB2_GPIO_PIN			GPIO_Pin_2
#define LCDDB2_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB3_GPIO_X			GPIOC
#define LCDDB3_GPIO_PIN			GPIO_Pin_3
#define LCDDB3_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB4_GPIO_X			GPIOC
#define LCDDB4_GPIO_PIN			GPIO_Pin_4
#define LCDDB4_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB5_GPIO_X			GPIOC
#define LCDDB5_GPIO_PIN			GPIO_Pin_5
#define LCDDB5_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB6_GPIO_X			GPIOC
#define LCDDB6_GPIO_PIN			GPIO_Pin_6
#define LCDDB6_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB7_GPIO_X			GPIOC
#define LCDDB7_GPIO_PIN			GPIO_Pin_7
#define LCDDB7_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC

#define LCDRS_GPIO_X			GPIOB
#define LCDRS_GPIO_PIN			GPIO_Pin_0
#define LCDRS_RCC_APB2PERIPH	RCC_APB2Periph_GPIOB
#define LCDRW_GPIO_X			GPIOB
#define LCDRW_GPIO_PIN			GPIO_Pin_1
#define LCDRW_RCC_APB2PERIPH	RCC_APB2Periph_GPIOB
#define LCDEN_GPIO_X			GPIOB
#define LCDEN_GPIO_PIN			GPIO_Pin_2
#define LCDEN_RCC_APB2PERIPH	RCC_APB2Periph_GPIOB

#define LCDCS1_GPIO_X			GPIOA
#define LCDCS1_GPIO_PIN			GPIO_Pin_0
#define LCDCS1_RCC_APB2PERIPH	RCC_APB2Periph_GPIOA
#define LCDCS2_GPIO_X			GPIOA
#define LCDCS2_GPIO_PIN			GPIO_Pin_1
#define LCDCS2_RCC_APB2PERIPH	RCC_APB2Periph_GPIOA
#define LCDCS3_GPIO_X			GPIOA
#define LCDCS3_GPIO_PIN			GPIO_Pin_5
#define LCDCS3_RCC_APB2PERIPH	RCC_APB2Periph_GPIOA
#endif


#ifdef BOARD_AUTOONOFF_STM32F103RCT6
#define LCDDB0_GPIO_X			GPIOC
#define LCDDB0_GPIO_PIN			GPIO_Pin_0
#define LCDDB0_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB1_GPIO_X			GPIOC
#define LCDDB1_GPIO_PIN			GPIO_Pin_1
#define LCDDB1_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB2_GPIO_X			GPIOC
#define LCDDB2_GPIO_PIN			GPIO_Pin_2
#define LCDDB2_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB3_GPIO_X			GPIOC
#define LCDDB3_GPIO_PIN			GPIO_Pin_3
#define LCDDB3_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB4_GPIO_X			GPIOC
#define LCDDB4_GPIO_PIN			GPIO_Pin_4
#define LCDDB4_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB5_GPIO_X			GPIOC
#define LCDDB5_GPIO_PIN			GPIO_Pin_5
#define LCDDB5_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB6_GPIO_X			GPIOC
#define LCDDB6_GPIO_PIN			GPIO_Pin_6
#define LCDDB6_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC
#define LCDDB7_GPIO_X			GPIOC
#define LCDDB7_GPIO_PIN			GPIO_Pin_7
#define LCDDB7_RCC_APB2PERIPH	RCC_APB2Periph_GPIOC

#define LCDRS_GPIO_X			GPIOB
#define LCDRS_GPIO_PIN			GPIO_Pin_0
#define LCDRS_RCC_APB2PERIPH	RCC_APB2Periph_GPIOB
#define LCDRW_GPIO_X			GPIOB
#define LCDRW_GPIO_PIN			GPIO_Pin_1
#define LCDRW_RCC_APB2PERIPH	RCC_APB2Periph_GPIOB
#define LCDEN_GPIO_X			GPIOB
#define LCDEN_GPIO_PIN			GPIO_Pin_2
#define LCDEN_RCC_APB2PERIPH	RCC_APB2Periph_GPIOB

#define LCDCS1_GPIO_X			GPIOA
#define LCDCS1_GPIO_PIN			GPIO_Pin_0
#define LCDCS1_RCC_APB2PERIPH	RCC_APB2Periph_GPIOA
#define LCDCS2_GPIO_X			GPIOA
#define LCDCS2_GPIO_PIN			GPIO_Pin_1
#define LCDCS2_RCC_APB2PERIPH	RCC_APB2Periph_GPIOA
#define LCDCS3_GPIO_X			GPIOA
#define LCDCS3_GPIO_PIN			GPIO_Pin_2
#define LCDCS3_RCC_APB2PERIPH	RCC_APB2Periph_GPIOA
#endif


// ????????????
#define SCREEN_ON	0x3f	// ????????????
#define SCREEN_OFF	0x3e	// ????????????

// LCD?????????
#define LCD_STATUS_FLAG_BUSY		0x80	// LCD????????????
#define LCD_STATUS_FLAG_ON_OFF		0x20	// LCD??????????????????
#define LCD_STATUS_FLAG_RESETING	0x10	// LCD??????????????????

// DDRAM??????
#define DDRAM_DISPLINE_SIZE 8	// ???????????????
#define DDRAM_DISPROW_SIZE  64	// ???????????????

#define SCREEN_CLEAN_BYTE 	0x00	// ????????????

#define SCREEN_BEGIN_LINE	0	// LCD???????????????
#define SCREEN_BEGIN_ROW	0	// LCD???????????????

// ??????????????????
#define DS19264_ALL_SCREEN_CLEAN	Ds19264CleanScreen(LEFT_SCRN);		\
										Ds19264CleanScreen(MID_SCRN);	\
										Ds19264CleanScreen(RIGHT_SCRN);	\
//										__NOP();	// ??????????????????????????????
	
// ??????????????????
#define DS19264_ALL_SCREEN_ON		DS19264WriteCmd(SCREEN_ON, LEFT_SCRN);		\
										DS19264WriteCmd(SCREEN_ON, MID_SCRN);	\
										DS19264WriteCmd(SCREEN_ON, RIGHT_SCRN);

// ????????????????????????????????? (0,0)
#define DS19264_ALL_SCREEN_START_0	Ds19264StartLineSet(0, LEFT_SCRN);		\
										Ds19264StartLineSet(0, MID_SCRN);	\
										Ds19264StartLineSet(0, RIGHT_SCRN);


// ds19264??????
typedef enum _tagDs19264Status
{
	STATUS_CHECK_BUSY = 0,
	STATUS_CHECK_ONOFF,
	STATUS_CHECK_RESET,
	DS19264_NOW_BUSY,
	DS19264_NOW_FREE,
	DS19264_NOW_ON,
	DS19264_NOW_OFF,
	DS19264_NOW_RESET,
	DS19264_NOW_NORMAL,
}TDs19264Stat;


// ds19264????????????
typedef enum _tagDs19264SelectScreen
{
	LEFT_SCRN = 0,
	MID_SCRN,
	RIGHT_SCRN,
}TDs19264ScrnSel;




void Ds19264Initial(void);
TDs19264Stat Ds19264ReadStatus(TDs19264Stat ds19264Status, TDs19264ScrnSel ds19264ScrnSel);
BYTE DS19264ReadCmd(TDs19264ScrnSel ds19264ScrnSel);
void DS19264WriteCmd(BYTE byCommand, TDs19264ScrnSel ds19264ScrnSel);
void Ds19264WriteData(BYTE byDisplyData, TDs19264ScrnSel ds19264ScrnSel);

BYTE Ds19264ReadChar(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel);
void Ds19264StartLineSet(UCHAR ulStartLine, TDs19264ScrnSel ds19264ScrnSel);
void Ds19264DispLocationSet(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel);
void Ds19264CleanScreen(TDs19264ScrnSel ds19264ScrnSel);
void Ds19264CSCtrl(TDs19264ScrnSel ds19264ScrnSel);




#endif
