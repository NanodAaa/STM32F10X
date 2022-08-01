#include "lcd_disp.h"


// 中文汉字储存缓冲区	
// 每行12个
// 最多4行
// 每个汉字32位
// g_byChineseBuf -- 可储存xx个汉字、每个汉字32位
// 最后一位为清屏数据
// 包括特殊符号
static BYTE g_byChineseBuf[CHINESE_BUF_SIZE + 1][CHINESE_CHARA_SIZE] = 
{
{0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
 0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00},	/*"开",0*/
{0x10,0x10,0xF0,0x1F,0x10,0xF0,0x00,0x40,0xE0,0x58,0x47,0x40,0x50,0x60,0xC0,0x00,
 0x40,0x22,0x15,0x08,0x16,0x21,0x00,0x00,0xFE,0x42,0x42,0x42,0x42,0xFE,0x00,0x00},	/*"始",1*/
{0x82,0x9A,0x96,0x93,0xFA,0x52,0x52,0x80,0x7E,0x12,0x12,0x12,0xF1,0x11,0x10,0x00,
 0x00,0x01,0x00,0xFE,0x93,0x92,0x93,0x92,0x92,0x92,0x92,0xFE,0x03,0x00,0x00,0x00},	/*"暂",2*/
{0x80,0x60,0xF8,0x07,0x00,0x04,0x74,0x54,0x55,0x56,0x54,0x54,0x74,0x04,0x00,0x00,
 0x00,0x00,0xFF,0x00,0x03,0x01,0x05,0x45,0x85,0x7D,0x05,0x05,0x05,0x01,0x03,0x00},	/*"停",3*/
{0x10,0x10,0x14,0xD4,0x54,0x54,0x54,0xFC,0x52,0x52,0x52,0xD3,0x12,0x10,0x10,0x00,
 0x40,0x40,0x50,0x57,0x55,0x55,0x55,0x7F,0x55,0x55,0x55,0x57,0x50,0x40,0x40,0x00},	/*"重",4*/
{0x00,0x17,0x15,0xD5,0x55,0x57,0x55,0x7D,0x55,0x57,0x55,0xD5,0x15,0x17,0x00,0x00,
 0x40,0x40,0x40,0x7F,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x7F,0x40,0x40,0x40,0x00},	/*"置",5*/
{0x40,0x40,0x42,0xCC,0x00,0x40,0xA0,0x9E,0x82,0x82,0x82,0x9E,0xA0,0x20,0x20,0x00,
 0x00,0x00,0x00,0x3F,0x90,0x88,0x40,0x43,0x2C,0x10,0x28,0x46,0x41,0x80,0x80,0x00},	/*"设",6*/
{0x00,0x17,0x15,0xD5,0x55,0x57,0x55,0x7D,0x55,0x57,0x55,0xD5,0x15,0x17,0x00,0x00,
 0x40,0x40,0x40,0x7F,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x7F,0x40,0x40,0x40,0x00},	/*"置",7*/
{0x04,0x84,0xE4,0x5C,0x44,0xC4,0x20,0x10,0xE8,0x27,0x24,0xE4,0x34,0x2C,0xE0,0x00,
 0x02,0x01,0x7F,0x10,0x10,0x3F,0x80,0x60,0x1F,0x09,0x09,0x3F,0x49,0x89,0x7F,0x00},	/*"确",8*/
{0x40,0x40,0x42,0xCC,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x3F,0x90,0x48,0x20,0x18,0x07,0x00,0x07,0x18,0x20,0x40,0x80,0x00},	/*"认",9*/
{0x02,0x02,0xFE,0x92,0x92,0x92,0xFE,0x02,0x06,0xFC,0x04,0x04,0x04,0xFC,0x00,0x00,
 0x08,0x18,0x0F,0x08,0x08,0x04,0xFF,0x04,0x84,0x40,0x27,0x18,0x27,0x40,0x80,0x00},	/*"取",10*/
{0x10,0x60,0x02,0x0C,0xC0,0x00,0xE2,0x2C,0x20,0x3F,0x20,0x28,0xE6,0x00,0x00,0x00,
 0x04,0x04,0x7C,0x03,0x00,0x00,0xFF,0x09,0x09,0x09,0x49,0x89,0x7F,0x00,0x00,0x00},	/*"消",11*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
 0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00},	/*"上",12*/
{0x24,0x24,0xA4,0xFE,0x23,0x22,0x00,0x10,0x08,0x94,0x67,0x24,0x94,0x0C,0x00,0x00,
 0x08,0x06,0x01,0xFF,0x01,0x06,0x00,0x89,0x89,0x44,0x4A,0x33,0x12,0x0A,0x06,0x00},	/*"移",13*/
{0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x02,0x02,0x42,0x82,0x02,0x02,0x02,0x02,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00},	/*"下",14*/
{0x24,0x24,0xA4,0xFE,0x23,0x22,0x00,0x10,0x08,0x94,0x67,0x24,0x94,0x0C,0x00,0x00,
 0x08,0x06,0x01,0xFF,0x01,0x06,0x00,0x89,0x89,0x44,0x4A,0x33,0x12,0x0A,0x06,0x00},	/*"移",15*/
{0x40,0x40,0x42,0xCC,0x00,0x00,0xFC,0x24,0xA4,0x24,0x22,0x22,0xA3,0x62,0x00,0x00,
 0x00,0x40,0x20,0x1F,0x20,0x58,0x47,0x50,0x48,0x45,0x42,0x45,0x48,0x50,0x40,0x00},	/*"返",16*/
{0x00,0x00,0xFE,0x02,0x02,0xF2,0x12,0x12,0x12,0xF2,0x02,0x02,0xFE,0x00,0x00,0x00,
 0x00,0x00,0x7F,0x20,0x20,0x27,0x24,0x24,0x24,0x27,0x20,0x20,0x7F,0x00,0x00,0x00},	/*"回",17*/
{0x40,0x40,0x42,0xCC,0x00,0x80,0x88,0x88,0xFF,0x88,0x88,0xFF,0x88,0x88,0x80,0x00,
 0x00,0x40,0x20,0x1F,0x20,0x40,0x50,0x4C,0x43,0x40,0x40,0x5F,0x40,0x40,0x40,0x00},	/*"进",18*/
{0x00,0x00,0x00,0x00,0x00,0x01,0xE2,0x1C,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x03,0x0C,0x30,0x40,0x80,0x80,0x00},	/*"入",19*/
 
{0x40,0x40,0x42,0xCC,0x00,0x20,0x22,0x22,0xA2,0x62,0x22,0x22,0x22,0x20,0x00,0x00,
 0x00,0x40,0x20,0x1F,0x20,0x44,0x4E,0x45,0x44,0x44,0x44,0x45,0x46,0x4C,0x40,0x00},	/*"运",20*/
{0x00,0x10,0x88,0xC4,0x33,0x00,0x40,0x42,0x42,0x42,0xC2,0x42,0x42,0x42,0x40,0x00,
 0x02,0x01,0x00,0xFF,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00},	/*"行",21*/
{0x10,0x10,0xD0,0xFF,0x90,0x14,0xE4,0xAF,0xA4,0xA4,0xA4,0xAF,0xE4,0x04,0x00,0x00,
 0x04,0x03,0x00,0xFF,0x00,0x89,0x4B,0x2A,0x1A,0x0E,0x1A,0x2A,0x4B,0x88,0x80,0x00},	/*"模",22*/
{0x10,0x10,0x90,0x90,0x90,0x90,0x90,0x10,0x10,0xFF,0x10,0x10,0x11,0x16,0x10,0x00,
 0x00,0x20,0x60,0x20,0x3F,0x10,0x10,0x10,0x00,0x03,0x0C,0x10,0x20,0x40,0xF8,0x00},	/*"式",23*/

{0x00,0x40,0x42,0x44,0x58,0x40,0x40,0x7F,0x40,0x40,0x50,0x48,0xC6,0x00,0x00,0x00,
 0x00,0x40,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0x00,0x00,0x00},	/*"当",24*/
{0x08,0x08,0xE8,0x29,0x2E,0x28,0xE8,0x08,0x08,0xC8,0x0C,0x0B,0xE8,0x08,0x08,0x00,
 0x00,0x00,0xFF,0x09,0x49,0x89,0x7F,0x00,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,0x00},	/*"前",25*/
{0x00,0x08,0x30,0x00,0xFF,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x22,0x2C,0x20,0x00,
 0x04,0x04,0x02,0x01,0xFF,0x80,0x40,0x30,0x0E,0x01,0x06,0x18,0x20,0x40,0x80,0x00},	/*"状",26*/
{0x00,0x04,0x84,0x84,0x44,0x24,0x54,0x8F,0x14,0x24,0x44,0x84,0x84,0x04,0x00,0x00,
 0x41,0x39,0x00,0x00,0x3C,0x40,0x40,0x42,0x4C,0x40,0x40,0x70,0x04,0x09,0x31,0x00},	/*"态",27*/

{0x80,0x60,0xF8,0x07,0x04,0x64,0x5C,0xC4,0x64,0x44,0x00,0xF8,0x00,0xFF,0x00,0x00,
 0x00,0x00,0xFF,0x00,0x20,0x62,0x22,0x1F,0x12,0x12,0x00,0x4F,0x80,0x7F,0x00,0x00},	/*"倒",28*/
{0x40,0x40,0x42,0xCC,0x00,0x40,0x40,0x40,0x40,0xFF,0x40,0x40,0x40,0x40,0x40,0x00,
 0x00,0x00,0x00,0x7F,0x20,0x10,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00},	/*"计",29*/
{0x00,0xFC,0x84,0x84,0x84,0xFC,0x00,0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x00,
 0x00,0x3F,0x10,0x10,0x10,0x3F,0x00,0x00,0x01,0x06,0x40,0x80,0x7F,0x00,0x00,0x00},	/*"时",30*/

{0x10,0x10,0x10,0xFF,0x10,0x90,0x00,0xFE,0x82,0x82,0x82,0x92,0xA2,0x9E,0x00,0x00,
 0x04,0x44,0x82,0x7F,0x01,0x00,0x00,0xFF,0x80,0x43,0x2C,0x10,0x2C,0x43,0x80,0x00},	/*"报",31*/
{0x12,0xEA,0xAF,0xAA,0xEA,0x0F,0xFA,0x02,0x88,0x8C,0x57,0x24,0x54,0x8C,0x84,0x00,
 0x02,0x02,0xEA,0xAA,0xAA,0xAB,0xAA,0xAB,0xAA,0xAA,0xAA,0xAA,0xEA,0x02,0x02,0x00},	/*"警",32*/
{0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x10,0xF0,0x00,0x00,0x00,
 0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x0F,0x00,0x00,0x00},	/*"中",33*/

{0x00,0x00,0xFC,0x04,0x04,0x04,0x14,0x15,0x56,0x94,0x54,0x34,0x14,0x04,0x04,0x00,
 0x40,0x30,0x0F,0x00,0x01,0x01,0x01,0x41,0x81,0x7F,0x01,0x01,0x01,0x05,0x03,0x00},	/*"序",34*/

{0x00,0xF8,0x01,0x06,0x00,0xF0,0x12,0x12,0x12,0xF2,0x02,0x02,0x02,0xFE,0x00,0x00,
 0x00,0xFF,0x00,0x00,0x00,0x1F,0x11,0x11,0x11,0x1F,0x00,0x40,0x80,0x7F,0x00,0x00},	/*"间",35*/


{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	/*"：",34*/

{0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	/*"！",35*/


{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	/*50 清屏数据*/
};


//	数字储存缓冲区
// 最后一位为清屏数据
// 包括英文
static BYTE g_byDigitBuf[DIGIT_BUF_SIZE + 1][DIGIT_CHARA_SIZE] =
{	
	{0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00},	/*"0"*/
	{0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00},	/*"1"*/
	{0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00},	/*"2"*/
	{0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00},	/*"3"*/
	{0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24},	/*"4"*/
	{0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00},	/*"5"*/
	{0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00},	/*"6"*/
	{0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00},	/*"7"*/
	{0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00},	/*"8"*/
	{0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00},	/*"9"*/

	{0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20},	/*"A",10*/
	{0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00},	/*"B",11*/
	{0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00},	/*"C",12*/
	{0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00},	/*"D",13*/
	{0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x24,0x24,0x24,0x24,0x17,0x00},	/*"e",14*/
	{0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00},	/*"E",15*/
	{0x00,0x80,0x80,0xE0,0x90,0x90,0x20,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},	/*"f",16*/
	{0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},	/*"i",17*/
	{0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},	/*"l",18*/
	{0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00},	/*"L",19*/
	{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F},	/*"m",20*/
	{0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20},	/*"n",21*/
	{0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00},	/*"o",22*/
	{0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x10,0x00},	/*"t",23*/
	{0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00},	/*"T",24*/
	{0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},	/*"I",25*/
	{0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20},	/*"u",26*/
		
	{0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x0F,0x01,0x01,0x01},	/*"+",27*/
	{0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00},	/*"*",28*/
		
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	/* 29 清屏数据*/
};


// 图片1储存区
static BYTE g_byBMP1Buf[BMP_BUF_SIZE][BMP_CHARA_SIZE] = 
{
{0xFF,0x01,0x01,0x01,0x01,0x01,0x81,0x71,0x61,0xC1,0x01,0x01,0xE1,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x81,0x81,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0xE1,0x01,0x01,0x01,0x01,0xE1,0xE1,0x81,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF},
{0xFF,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x01,0x03,0x06,0x0F,0x00,0x07,0x0D},
{0x0F,0x06,0x0C,0x0C,0x00,0x0F,0x01,0x01,0x0F,0x08,0x0F,0x09,0x09,0x0F,0x00,0x0F},
{0x09,0x0D,0x0F,0x08,0x08,0x00,0x08,0x0F,0x02,0x03,0x06,0x1C,0x10,0x0F,0x09,0x09},
{0x0F,0x1C,0x00,0x00,0x0F,0x09,0x0F,0x0C,0x08,0x80,0x00,0x80,0xC0,0x40,0x40,0x40},
{0x60,0x20,0x20,0x20,0x60,0x40,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x40,0x60,0x20},
{0x30,0x10,0x10,0x10,0x18,0x08,0x08,0x08,0x08,0x18,0x10,0x20,0x60,0x40,0x80,0x80},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x80,0x20,0x08,0x04,0x00,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x0E,0x78,0xC0,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x1C,0x03,0x01,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01},
{0x03,0x06,0x0C,0x38,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30},
{0x1F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x0F,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x01,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80},
{0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x03,0x06,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03},
{0x04,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x01,0x06,0x0C,0x18,0x10,0x30,0x20,0x60,0x40,0x40,0xC0,0x80,0x80},
{0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x40,0x40,0x40,0x20,0x20},
{0x10,0x10,0x18,0x0C,0x04,0x06,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
{0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF},/*"笑脸",0*/

};
	

// 图片2储存区
BYTE g_byBMP2Buf[BMP_BUF_SIZE][BMP_CHARA_SIZE] = 
{
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80},
{0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x18,0x0C,0x06,0x03,0x01,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x0F,0x00,0x03,0x0E,0x18,0x60,0x80},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
{0x0E,0x38,0x60,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0xF0,0x1E,0x0F,0x70,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFE,0x01,0x00,0x00,0x00,0x00,0x01,0x01},
{0x03,0x02,0x0C,0xB8,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xC0,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x1E,0xE0,0x00,0x20,0x20,0x30,0x10,0x10,0x10,0x10,0x10,0x18,0x08,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x02,0x06,0x04,0x04,0x04,0x04,0x08,0x08},
{0x08,0x08,0x08,0x18,0x10,0x70,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0xC0,0x70,0x0F,0x00,0x00,0x08,0x08,0x08,0x08,0x0C,0x04},
{0x07,0x0C,0x14,0x60,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x1F},
{0x00,0x00,0x00,0x01,0x03,0x04,0x18,0x30,0xC0,0x80,0x00,0x00,0x00,0x00,0x80,0xE0},
{0x38,0x07,0x01,0x00,0x00,0x00,0x03,0x0E,0x38,0xC0,0x80,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0x08,0x08,0x08},
{0x08,0x04,0x06,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x03,0x7C,0xA0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40},
{0x40,0x40,0x60,0x20,0x20,0x30,0x1B,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x70,0x0E,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x01,0x07,0x0C,0x30,0xE0,0x80,0x00,0x00,0x00,0x00,0xFF,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x06,0x04,0x38,0x0E,0x03,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0E,0x78,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x37,0x20,0x20,0x20},
{0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x0F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x06,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x03,0x02,0x82,0x02,0x02,0x06,0x04,0x04,0x04,0x04,0x04},
{0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x03,0x1E,0x0C,0x07,0x01,0x10,0x00,0x00,0x0F,0x31,0x3F,0x00},
{0x10,0x00,0x0E,0x1A,0x1E,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x80,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xFE,0x52,0x52,0x5E,0x70,0x00},
{0x07,0x0C,0xFE,0x02,0x02,0x00,0x00,0x00,0x00,0xFE,0x0C,0x18,0x70,0xFE,0x00,0x00},
{0xF0,0x10,0xF0,0x80,0x80,0xF0,0x30,0xF0,0x00,0xF0,0x90,0xD0,0x60,0x00,0xF8,0x48},
{0xFF,0x00,0x00,0xFF,0x1E,0x70,0xC0,0x00,0xF0,0xB0,0xF0,0xC0,0x70,0x70,0xC0,0x80},/*"菜单",0*/
};


// ds19264写指令
void DS19264WriteCmd(BYTE byCommand, TDs19264ScrnSel ds19264ScrnSel)
{
	GPIO_InitTypeDef GPIO_InitStructure;	// GPIO配置结构体
	
	while(DS19264_NOW_BUSY == Ds19264ReadStatus(STATUS_CHECK_BUSY, ds19264ScrnSel));	// 检测繁忙

	// EN 下降沿
	// RW = 0
	// RS = 0

	Ds19264CSCtrl(ds19264ScrnSel); // CS1/CS2/CS3 = 0

	GPIO_ResetBits(LCDRW_GPIO_X, LCDRW_GPIO_PIN);	// RW = 0
	GPIO_ResetBits(LCDRS_GPIO_X, LCDRS_GPIO_PIN);	// RS = 0

	uint16_t uTemp = GPIO_ReadOutputData(LCDDB0_GPIO_X);	// 获取ODR 16位寄存器
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 模式设置为推挽输出，读取LCD引脚电平
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = 0xFF; 			//DB7..DB0
		GPIO_Init(LCDDB7_GPIO_X, &GPIO_InitStructure);	
	
	uTemp &= 0xFF00;  // 0xFF00
	uTemp |= byCommand;
		
	GPIO_Write(LCDDB0_GPIO_X, uTemp);	// 写入byDisplyData


	GPIO_SetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);		// EN = 1
	GPIO_ResetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);	// EN = 0

	LCD_CS_DESELECT_ALL

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 模式设置为上拉输入，读取LCD引脚电平
	GPIO_Init(LCDDB7_GPIO_X, &GPIO_InitStructure);
	
}


// Ds19264写入显示数据
void Ds19264WriteData(BYTE byDisplyData, TDs19264ScrnSel ds19264ScrnSel)
{
	GPIO_InitTypeDef GPIO_InitStructure;	// GPIO配置结构体

	while(DS19264_NOW_BUSY == Ds19264ReadStatus(STATUS_CHECK_BUSY, ds19264ScrnSel));	// 检测繁忙

	Ds19264CSCtrl(ds19264ScrnSel); // CS1/CS2/CS3 = 0

	GPIO_SetBits(LCDRS_GPIO_X, LCDRS_GPIO_PIN);		// RS = 1
	GPIO_ResetBits(LCDRW_GPIO_X, LCDRW_GPIO_PIN);	// RW = 0

	uint16_t uTemp =  GPIO_ReadOutputData(LCDDB0_GPIO_X);	// 获取ODR 16位寄存器

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 模式设置为推挽输出，读取LCD引脚电平
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = 0xFF;				//DB7..DB0
		GPIO_Init(LCDDB7_GPIO_X, &GPIO_InitStructure);	

	uTemp &= 0xFF00;  // 0xFF00
	uTemp |= byDisplyData;
	
	GPIO_Write(LCDDB0_GPIO_X, uTemp);	// 写入byDisplyData
	
	GPIO_SetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);		// EN = 1
	GPIO_ResetBits(LCDEN_GPIO_X, LCDEN_GPIO_PIN);	// EN = 0

	LCD_CS_DESELECT_ALL	// 取消所有片选

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 模式设置为上拉输入，读取LCD引脚电平
	GPIO_Init(LCDDB7_GPIO_X, &GPIO_InitStructure);		
	
}


// Ds19264输入字符 
// uiDispLine -- 显示行设置（X），取值范围 0 ~ 7H
// uiDispRow  -- 显示列设置（Y），取值范围 0 ~ 3FH
// ds19264ScrnSel -- 屏幕选择
void Ds19264WriteChar(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel, BYTE byChar)
{
	Ds19264DispLocationSet(uiDispLine, uiDispRow, ds19264ScrnSel); // 设置显示位置、显示屏幕

	Ds19264WriteData(byChar, ds19264ScrnSel);	// 写入字符
}


// Ds19264输入字符串
// uiDispLine -- 显示行设置（X），取值范围 0 ~ 7H
// uiDispRow  -- 显示列设置（Y），取值范围 0 ~ 3FH
// ds19264ScrnSel -- 屏幕选择
void Ds19264WriteString(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel, BYTE* byString)
{
	Ds19264DispLocationSet(uiDispLine, uiDispRow, ds19264ScrnSel); // 设置显示位置、显示屏幕

	// 写入字符串
	while(*byString)
	{
		Ds19264WriteData(*byString, ds19264ScrnSel);
		byString++;
	}
}


// Ds19264中指定位置写入一个中文汉字
// uiDispLine -- 显示行设置（X），取值范围 0 ~ 7H
// uiDispRow  -- 显示列设置（Y），取值范围 0 ~ 3FH
// byChineseBuf -- 中文汉字缓冲区号
void Ds19264WriteChinese(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel, UINT byChineseBuf)
{
	UINT uiCharaCount = 0;	// 字节计数器

	uiDispLine *= CHINESE_LINE_CONSTANT;
	uiDispRow  *= CHINESE_ROW_CONSTANT;

	Ds19264DispLocationSet(uiDispLine, uiDispRow, ds19264ScrnSel); // 设置显示位置、显示屏幕

	// 写入汉字
	while(uiCharaCount < CHINESE_CHARA_SIZE)
	{
		// 写完上半部分后，X+1
		if(uiCharaCount == 16)
		{
			Ds19264DispLocationSet(uiDispLine + 1, uiDispRow, ds19264ScrnSel);
		}
		
		Ds19264WriteData(g_byChineseBuf[byChineseBuf][uiCharaCount], ds19264ScrnSel);
		uiCharaCount++;
	}
	Ds19264DispLocationSet(uiDispLine, uiDispRow, ds19264ScrnSel);	// X还原
}


// Ds19264显示数字
// uiDispLine -- 显示行设置（X），取值范围 0 ~ 7H -- 0 ~ 7
// uiDispRow  -- 显示列设置（Y），取值范围 0 ~ 3FH -- 0 ~ 3
// byDigitBuf -- 数字缓冲区号
void Ds19264WriteDigit(UCHAR uiDispLine, UCHAR uiDispRow, TDs19264ScrnSel ds19264ScrnSel, UINT byDigitBuf)
{
	UINT uiCharaCount = 0;

	uiDispLine *= DIGIT_LINE_CONSTANT;
	uiDispRow  *= DIGIT_ROW_CONSTANT;
	
	Ds19264DispLocationSet(uiDispLine, uiDispRow, ds19264ScrnSel); // 设置显示位置、显示屏幕

	// 写入数字
	while(uiCharaCount < DIGIT_CHARA_SIZE)
	{
		if(uiCharaCount == 8)
		{
			Ds19264DispLocationSet(uiDispLine + 1, uiDispRow, ds19264ScrnSel);
		}
		
		Ds19264WriteData(g_byDigitBuf[byDigitBuf][uiCharaCount], ds19264ScrnSel);
		uiCharaCount++;
	}

	Ds19264DispLocationSet(uiDispLine, uiDispRow, ds19264ScrnSel);	// X还原
}


// Ds19264显示BMP
// p_byBMP -- 图片的储存区号
void Ds19264DisplayBMP(BYTE* p_byBMP)
{
	UINT  uiBufCount;		// 数组X计数
	UINT  uiCharaCount;		// 数组Y计数
	UCHAR ucScreenLineCount = SCREEN_BEGIN_LINE;	// 屏幕X轴计数
	UCHAR ucScreenRowCount  = SCREEN_BEGIN_ROW;		// 屏幕Y轴计数
	BYTE  byBMPData;		// 暂存图片数据		 *方便调试
	
	TDs19264ScrnSel ds19264ScrnSel;
	ds19264ScrnSel = LEFT_SCRN; 	// 初始为左屏
	Ds19264DispLocationSet(ucScreenLineCount, ucScreenRowCount, ds19264ScrnSel);	// 左屏幕开头显示

	// 逐行显示
	// 一行8格
	for(uiBufCount = 0; uiBufCount < BMP_BUF_SIZE; uiBufCount++)
	{
		// 前面的屏写完后切换屏幕
		if(uiBufCount % ((BMP_BUF_SIZE / 8) / SCREEN_NUMBER) == 0 && uiBufCount > 0)
		{
			if(ds19264ScrnSel == LEFT_SCRN)
			{
				ds19264ScrnSel = MID_SCRN;
				Ds19264DispLocationSet(ucScreenLineCount, ucScreenRowCount, ds19264ScrnSel);	// 屏幕开头显示
			}
			else if(ds19264ScrnSel == MID_SCRN)
			{
				ds19264ScrnSel = RIGHT_SCRN;
				Ds19264DispLocationSet(ucScreenLineCount, ucScreenRowCount, ds19264ScrnSel);	// 屏幕开头显示
			}
			else if(ds19264ScrnSel == RIGHT_SCRN)
			{
				ds19264ScrnSel = LEFT_SCRN;
			}
		}

		// 一行写完后切换下一行
		if((uiBufCount % (BMP_BUF_SIZE / 8)) == 0 && uiBufCount > 0)
		{
			ucScreenLineCount += 1;
			Ds19264DispLocationSet(ucScreenLineCount, ucScreenRowCount, ds19264ScrnSel);	// 第二行、左屏幕开头显示
		}
		
		for(uiCharaCount = 0; uiCharaCount < BMP_CHARA_SIZE; uiCharaCount++)
		{
			byBMPData = *(p_byBMP + (uiBufCount * BMP_CHARA_SIZE) + uiCharaCount);	// 图片缓冲区寻址
			
			Ds19264WriteData(byBMPData, ds19264ScrnSel);	// 写入图片数据
		}
		
	}

}












































