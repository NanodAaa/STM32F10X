#ifndef _LCD_MENU_H_
#define _LCD_MENU_H_


#include "ds19264.h"
#include "lcd_disp.h"
#include "key.h"
#include "beep.h"
#include "delay.h"


// 状态机状态
typedef enum _tagMenuStateMachineStat
{
	STATMACHINE_SELECT_MENU = 0,
	STATMACHINE_MENU_OPTION,
	STATMACHINE_SEQUENTIAL,
	STATMACHINE_CLOCK_SET,
}TMenuStateMachineStat;


// 测试板运行模式
// 模式1 —— ACC
// 模式2 —— B+
typedef enum _tagRunningMode
{
	RUNNING_MODE_ACC = 0,
	RUNNING_MODE_BP,
}TRunningMode;


// 测试板当前状态
// Ton  -- 开机时间
// Toff -- 关机时间
typedef enum _tagRunningState
{
	RUNNING_STATE_TON = 0,
	RUNNING_STATE_TOFF,
	RUNNING_STATE_IDLE,
	RUNNING_STATE_WARNING,
}TRunningState;


// 按键对应文字
// 按键 —— 开始
// 按键 —— 暂停
// 按键 —— 重置
// 按键 —— 设置
// 按键 —— 确认
// 按键 —— 取消
// 按键 —— 上移
// 按键 —— 下移
// 按键 —— 返回
// 按键 —— 进入
typedef enum _tagKeyChara
{
	KEYCHARA_START = 0,
	KEYCHARA_STOP,
	KEYCHARA_RESET,
	KEYCHARA_SETTING,
	KEYCHARA_CONFIRM,
	KEYCHARA_CANCEL,
	KEYCHARA_MOVEUP,
	KEYCHARA_MOVEDOWN,
	KEYCHARA_RETURN,
	KEYCHARA_ENTER,
}TKeyChara;


// 当前显示的菜单
// 主界面
// 设置界面
// 设置——运行模式
// 设置——时序设置
// 设置——时间设置
typedef enum _tagMenuDisplay
{
	MENU_DISPLAY_MAIN = 0,
	MENU_DISPLAY_OPTION,
	MENU_DISPLAY_OPTION_RUNNINGMODE,
	MENU_DISPLAY_OPTION_SEQUENTIAL,
	MENU_DISPLAY_OPTION_CLOCK,
}TMenuDisplay;


// 指针位置
typedef enum _tagMenuCoursePos
{
	COURSE_POS_FIRST = 0,
	COURSE_POS_SECOND,
	COURSE_POS_THIRD,
}TMenuCoursePos;


// 主界面数据结构体
// 测试板运行模式，默认ACC
// 测试板运行状态，默认Ton
// Ton剩余时间
// Toff剩余时间
// 按键文字
typedef struct _tagMenuMainData
{
	TRunningMode  RunningMode;	
	TRunningState RunningState;	
	TMenuCoursePos MenuCoursePos;
	UINT byTonVal;			
	UINT byToffVal;			
}SMenuMainData;

/*
// 设置界面数据结构体
typedef struct _tagMenuOptionData
{
	
}SMenuOptionData;
*/

/*
// 运行模式设置数据结构体
typedef struct _tagOptionRunningModeData
{
	
}SOptionRunningModeData;


// 运行时序设置数据结构体
typedef struct _tagOptionSquentialData
{
	
}SOptionSquentialData;


// 时间设置数据结构体
typedef struct _tagOptionClockData
{
	
}SOptionClockData;
*/






void MenuDispBeginPic(void);
void MenuInitial(void);
void MenuStateMachine(void);
void MenuDisplay(void);
void Menu_Main(void);
void Menu_Option(void);
void Menu_Option_RunningMode(void);
void Menu_Option_Sequential(void);
void Menu_Option_Clock(void);


void CourseMoveUp(void);
void CourseMoveDown(void);





/*

switch(g_KeyState)
			{
				// KEY1
				// 
				case GENERAL_KEYSTATE_KEY1_PRES:
				{
					
				}
				// KEY2
				// 
				case GENERAL_KEYSTATE_KEY2_PRES:
				{
					break;
				}
				// KEY3
				// 
				case GENERAL_KEYSTATE_KEY3_PRES:
				{
					break;
				}
				// KEY4
				// 
				case GENERAL_KEYSTATE_KEY4_PRES:
				{
					
				}
				// 无按键按下
				// 
				case GENERAL_KEYSTATE_NOKEYPRES:
				{
					break;
				}
			}

*/






























#endif
