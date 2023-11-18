#include "lcd_menu.h"

extern TGeneralKeyState g_KeyState;		// 全局按键状态，默认无按下
extern BYTE g_byBMP2Buf;

static TMenuStateMachineStat g_MenuStateMachineStat;	// 状态机状态
static TMenuDisplay  g_MenuDisplay;	// 当前显示的菜单，默认主菜单
static SMenuMainData  MenuMainData;

// 系统开机图
// 上电即显示
// 显示“图片2”
void MenuDispBeginPic(void)
{
	// 显示图片2
	Ds19264DisplayBMP(&g_byBMP2Buf);

	// 延时 3s

}


// 菜单初始化
void MenuInitial(void)
{
	MenuMainData.byTonVal = 999;	// Ton时间
	MenuMainData.byToffVal = 999;	// Toff时间
	MenuMainData.RunningMode = RUNNING_MODE_ACC;		// 默认ACC模式
	MenuMainData.RunningState = RUNNING_STATE_IDLE;		// 默认处于IDLE状态
	MenuMainData.MenuCoursePos = COURSE_POS_FIRST;		// 指针默认第一行
	g_MenuDisplay = MENU_DISPLAY_OPTION_SEQUENTIAL;		// 当前显示的菜单，默认主菜单
	g_MenuStateMachineStat = STATMACHINE_SELECT_MENU;	// 状态机状态
}


// 系统菜单界面状态机
// 位于Process100ms，每100ms执行一次
// 用于更改数值
void MenuStateMachine(void)
{
	// 扫描按键状态给 g_KeyState 在Process10Ms中完成
	switch(g_MenuStateMachineStat)
	{
		// 主菜单
		case STATMACHINE_SELECT_MENU:
		{		
			switch(g_KeyState)
			{
				// KEY1
				// 进入设置界面
				case GENERAL_KEYSTATE_KEY1_PRES:
				{
					g_MenuDisplay = MENU_DISPLAY_OPTION;	// 显示设置界面
					g_MenuStateMachineStat = STATMACHINE_MENU_OPTION;	// 状态机切换至选项菜单
					DS19264_ALL_SCREEN_CLEAN	// 清屏
					break;
				}
				// KEY2
				// 无处理
				case GENERAL_KEYSTATE_KEY2_PRES:
				{
					break;
				}
				// KEY3
				// 无处理
				case GENERAL_KEYSTATE_KEY3_PRES:
				{
					break;
				}
				// KEY4
				// 开始设备运作
				case GENERAL_KEYSTATE_KEY4_PRES:
				{
					break;
				}
				// 无按键按下
				// 停留在
				case GENERAL_KEYSTATE_NOKEYPRES:
				{
					break;
				}
			}
		}

		// 设置菜单
		case STATMACHINE_MENU_OPTION:
		{
			switch(g_KeyState)
			{
				// KEY1
				// 返回主界面
				case GENERAL_KEYSTATE_KEY1_PRES:
				{
					g_MenuDisplay = MENU_DISPLAY_MAIN;	// 显示主菜单
					g_MenuStateMachineStat = STATMACHINE_SELECT_MENU;	// 返回主菜单
					DS19264_ALL_SCREEN_CLEAN	// 清屏
					break;
				}
				// KEY2
				// 光标上移
				case GENERAL_KEYSTATE_KEY2_PRES:
				{
					CourseMoveUp();	// 上移
					DS19264_ALL_SCREEN_CLEAN	// 清屏
					break;
				}
				// KEY3
				// 光标下移
				case GENERAL_KEYSTATE_KEY3_PRES:
				{
					CourseMoveDown();	// 下移
					DS19264_ALL_SCREEN_CLEAN	// 清屏
					break;
				}
				// KEY4
				// 确认
				case GENERAL_KEYSTATE_KEY4_PRES:
				{
					// 光标在第一行 -- 切换运行模式
					if(MenuMainData.MenuCoursePos == COURSE_POS_FIRST)
					{
						if(MenuMainData.RunningMode == RUNNING_MODE_ACC)
						{
							MenuMainData.RunningMode = RUNNING_MODE_BP;
							
						}
						else if(MenuMainData.RunningMode == RUNNING_MODE_BP)
						{
							MenuMainData.RunningMode = RUNNING_MODE_ACC;
						}
					}
					// 光标在第二行 -- 进入时序设置
					else if(MenuMainData.MenuCoursePos == COURSE_POS_SECOND)
					{
						// 显示时序设置子菜单
						g_MenuDisplay = MENU_DISPLAY_OPTION_SEQUENTIAL;
						g_MenuStateMachineStat = STATMACHINE_SEQUENTIAL;	// 状态机切换至时序设置
					}
					// 光标在第三行 -- 进入时间设置
					else if(MenuMainData.MenuCoursePos == COURSE_POS_THIRD)
					{
						g_MenuDisplay = MENU_DISPLAY_OPTION_CLOCK;			// 显示时间设置菜单
						g_MenuStateMachineStat = STATMACHINE_CLOCK_SET;		// 状态机切换至时间设置
					}
					DS19264_ALL_SCREEN_CLEAN	// 清屏
					break;			
				}
				// 无按键按下
				// 
				case GENERAL_KEYSTATE_NOKEYPRES:
				{
					break;
				}
			}

			// 时序设置菜单
			case STATMACHINE_SEQUENTIAL:
			{
				switch(g_KeyState)
				{
					// KEY1
					// 返回设置菜单
					case GENERAL_KEYSTATE_KEY1_PRES:
					{
						g_MenuDisplay = MENU_DISPLAY_OPTION;				// 显示设置菜单
						g_MenuStateMachineStat = STATMACHINE_MENU_OPTION;	// 状态机进入设置菜单
						DS19264_ALL_SCREEN_CLEAN	// 清屏
						break;
					}
					// KEY2
					// 上移
					case GENERAL_KEYSTATE_KEY2_PRES:
					{
						CourseMoveUp();				// 上移
						DS19264_ALL_SCREEN_CLEAN	// 清屏
						break;
					}
					// KEY3
					// 下移
					case GENERAL_KEYSTATE_KEY3_PRES:
					{
						CourseMoveDown();			// 下移
						DS19264_ALL_SCREEN_CLEAN	// 清屏
						break;
					}
					// KEY4
					// 确认
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
			}
		}
//		DS19264_ALL_SCREEN_CLEAN		// 清屏
	}
	// 设置菜单
//	switch()
}


// 当前显示的菜单
// 在Process100ms中调用
void MenuDisplay(void)
{
	switch(g_MenuDisplay)
	{
		case MENU_DISPLAY_MAIN:
		{
			Menu_Main();
			break;
		}
		case MENU_DISPLAY_OPTION:
 		{
			Menu_Option();
			break;
		}
		case MENU_DISPLAY_OPTION_RUNNINGMODE:
		{
			Menu_Option_RunningMode();
			break;
		}
		case MENU_DISPLAY_OPTION_SEQUENTIAL:
		{
			Menu_Option_Sequential();
			break;
		}
		case MENU_DISPLAY_OPTION_CLOCK:
		{
			Menu_Option_Clock();
			break;
		}
	}
}


// 主界面
void Menu_Main(void)
{
	Ds19264WriteChinese(0, 0, LEFT_SCRN, 22);	// “模”
	Ds19264WriteChinese(0, 1, LEFT_SCRN, 23);	// “式”
	Ds19264WriteChinese(0, 2, LEFT_SCRN, 35);	// '：'
	Ds19264WriteChinese(1, 0, LEFT_SCRN, 26);	// “状”
	Ds19264WriteChinese(1, 1, LEFT_SCRN, 27);	// “态”
	Ds19264WriteChinese(1, 2, LEFT_SCRN, 35);	// “：”
	Ds19264WriteChinese(3, 0, LEFT_SCRN, 6);	// “设”
	Ds19264WriteChinese(3, 1, LEFT_SCRN, 7);	// “置”
	Ds19264WriteChinese(3, 1, RIGHT_SCRN, 0);	// “开”
	Ds19264WriteChinese(3, 2, RIGHT_SCRN, 1);	// “始”

	// 显示运行模式
	if(MenuMainData.RunningMode == RUNNING_MODE_ACC)
	{
		Ds19264WriteDigit(0, 6, LEFT_SCRN, 10);	// 'A'
		Ds19264WriteDigit(0, 7, LEFT_SCRN, 12);	// 'C'
		Ds19264WriteDigit(0, 0, MID_SCRN, 12);	// 'C'
	}
	else
	{
		Ds19264WriteDigit(0, 5, MID_SCRN, 11);	// 'B'
		Ds19264WriteDigit(0, 6, MID_SCRN, 26);	// '+'
	}

	// 显示运行状态
	if(MenuMainData.RunningState == RUNNING_STATE_TON)
	{
		Ds19264WriteDigit(1, 6, LEFT_SCRN, 24);	// 'T'
		Ds19264WriteDigit(1, 7, LEFT_SCRN, 22);	// 'o'
		Ds19264WriteDigit(1, 0, MID_SCRN, 21);	// 'n'
	}
	else if(MenuMainData.RunningState == RUNNING_STATE_TOFF)
	{
		Ds19264WriteDigit(1, 6, LEFT_SCRN, 24);	// 'T'
		Ds19264WriteDigit(1, 7, LEFT_SCRN, 22);	// 'o'
		Ds19264WriteDigit(1, 0, MID_SCRN, 16);	// 'f'
		Ds19264WriteDigit(1, 1, MID_SCRN, 16);	// 'f'
	}
	else if(MenuMainData.RunningState == RUNNING_STATE_IDLE)
	{
		Ds19264WriteDigit(1, 6, LEFT_SCRN, 25);	// 'I'
		Ds19264WriteDigit(1, 7, LEFT_SCRN, 13);	// 'D'
		Ds19264WriteDigit(1, 0, MID_SCRN, 19);	// 'L'
		Ds19264WriteDigit(1, 1, MID_SCRN, 15);	// 'E'
	}
	else
	{
		Ds19264WriteChinese(1, 3, LEFT_SCRN, 31);	// “报”
		Ds19264WriteChinese(1, 0, MID_SCRN, 32);	// “警”
		Ds19264WriteChinese(1, 1, MID_SCRN, 33);	// “中”
		Ds19264WriteChinese(1, 2, MID_SCRN, 36);	// “！” 
	}
}


// 设置菜单界面
void Menu_Option(void)
{
	Ds19264WriteChinese(0, 0, LEFT_SCRN, 20);	// “运”
	Ds19264WriteChinese(0, 1, LEFT_SCRN, 21);	// “行”
	Ds19264WriteChinese(0, 2, LEFT_SCRN, 22);	// “模”
	Ds19264WriteChinese(0, 3, LEFT_SCRN, 23);	// “式”
//	Ds19264WriteChinese(0, 0, MID_SCRN, 34);	// “：”

	Ds19264WriteChinese(1, 0, LEFT_SCRN, 30);	// “时”
	Ds19264WriteChinese(1, 1, LEFT_SCRN, 34);	// “序”
	Ds19264WriteChinese(1, 2, LEFT_SCRN, 6);	// “设”
	Ds19264WriteChinese(1, 3, LEFT_SCRN, 7);	// “置”
	
	Ds19264WriteChinese(2, 0, LEFT_SCRN, 30);	// “时”
	Ds19264WriteChinese(2, 1, LEFT_SCRN, 35);	// “间”
	Ds19264WriteChinese(2, 2, LEFT_SCRN, 6);	// “设”
	Ds19264WriteChinese(2, 3, LEFT_SCRN, 7);	// “置”

	// 显示运行模式
	if(MenuMainData.RunningMode == RUNNING_MODE_ACC)
	{
		Ds19264WriteDigit(0, 5, MID_SCRN, 10);	// 'A'
		Ds19264WriteDigit(0, 6, MID_SCRN, 12);	// 'C'
		Ds19264WriteDigit(0, 7, MID_SCRN, 12);	// 'C'
	}
	else
	{
		Ds19264WriteDigit(0, 5, MID_SCRN, 11);	// 'B'
		Ds19264WriteDigit(0, 6, MID_SCRN, 26);	// '+'
	}
	
	Ds19264WriteChinese(3, 0, LEFT_SCRN, 16);	// “返”
	Ds19264WriteChinese(3, 1, LEFT_SCRN, 17);	// “回”
	Ds19264WriteChinese(3, 3, LEFT_SCRN, 12);	// “上”
	Ds19264WriteChinese(3, 0, MID_SCRN, 13);	// “移”
	Ds19264WriteChinese(3, 2, MID_SCRN, 14);	// “下”
	Ds19264WriteChinese(3, 3, MID_SCRN, 13);	// “移”
	Ds19264WriteChinese(3, 2, RIGHT_SCRN, 8);	// “确”
	Ds19264WriteChinese(3, 3, RIGHT_SCRN, 9);	// “认”

	// 显示指针
	switch(MenuMainData.MenuCoursePos)
	{
		case COURSE_POS_FIRST:
		{
			Ds19264WriteDigit(0, 2, RIGHT_SCRN, 27);
			break;
		}
		case COURSE_POS_SECOND:
		{
			Ds19264WriteDigit(1, 2, MID_SCRN, 27);
			break;
		}
		case COURSE_POS_THIRD:
		{
			Ds19264WriteDigit(2, 2, MID_SCRN, 27);
			break;
		}
	}
}


// 设置——运行模式
void Menu_Option_RunningMode(void)
{
	
}


// 设置——时序设置
void Menu_Option_Sequential(void)
{
	Ds19264WriteDigit(0, 0, LEFT_SCRN, 24);	// “T”
	Ds19264WriteDigit(0, 1, LEFT_SCRN, 22);	// “o”
	Ds19264WriteDigit(0, 2, LEFT_SCRN, 21);	// “n”
	Ds19264WriteDigit(1, 0, LEFT_SCRN, 24);	// “T”
	Ds19264WriteDigit(1, 1, LEFT_SCRN, 22);	// “o”
	Ds19264WriteDigit(1, 2, LEFT_SCRN, 16);	// “f”
	Ds19264WriteDigit(1, 3, LEFT_SCRN, 16);	// “f”
	Ds19264WriteDigit(2, 0, LEFT_SCRN, 24);	// “T”
	Ds19264WriteDigit(2, 1, LEFT_SCRN, 20);	// “m”
	Ds19264WriteDigit(2, 2, LEFT_SCRN, 26);	// “u”
	Ds19264WriteDigit(2, 3, LEFT_SCRN, 23);	// “t”
	Ds19264WriteDigit(2, 4, LEFT_SCRN, 14);	// “e”

	Ds19264WriteChinese(3, 0, LEFT_SCRN, 16);	// “返”
	Ds19264WriteChinese(3, 1, LEFT_SCRN, 17);	// “回”
	Ds19264WriteChinese(3, 3, LEFT_SCRN, 12);	// “上”
	Ds19264WriteChinese(3, 0, MID_SCRN, 13);	// “移”
	Ds19264WriteChinese(3, 2, MID_SCRN, 14);	// “下”
	Ds19264WriteChinese(3, 3, MID_SCRN, 13);	// “移”
	Ds19264WriteChinese(3, 2, RIGHT_SCRN, 8);	// “确”
	Ds19264WriteChinese(3, 3, RIGHT_SCRN, 9);	// “认”

	// 显示指针
	switch(MenuMainData.MenuCoursePos)
	{
		case COURSE_POS_FIRST:
		{
			Ds19264WriteDigit(0, 2, RIGHT_SCRN, 27);
			break;
		}
		case COURSE_POS_SECOND:
		{
			Ds19264WriteDigit(1, 2, MID_SCRN, 27);
			break;
		}
		case COURSE_POS_THIRD:
		{
			Ds19264WriteDigit(2, 2, MID_SCRN, 27);
			break;
		}
	}
}


// 设置——时间设置
void Menu_Option_Clock(void)
{
}


// 光标上移
void CourseMoveUp(void)
{
	if(MenuMainData.MenuCoursePos == COURSE_POS_SECOND)
	{
		MenuMainData.MenuCoursePos = COURSE_POS_FIRST;
	}
	else if(MenuMainData.MenuCoursePos == COURSE_POS_THIRD)
	{
		MenuMainData.MenuCoursePos = COURSE_POS_SECOND;
	}
}


// 光标下移
void CourseMoveDown(void)
{
	if(MenuMainData.MenuCoursePos == COURSE_POS_FIRST)
	{
		MenuMainData.MenuCoursePos = COURSE_POS_SECOND;
	}
	else if(MenuMainData.MenuCoursePos == COURSE_POS_SECOND)
	{
		MenuMainData.MenuCoursePos = COURSE_POS_FIRST;
	}
}



