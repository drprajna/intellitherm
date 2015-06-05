#ifndef _PUBLIC_H
#define _PUBLIC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_types.h"
#include "hal_board.h"
#include "hal_uart.h"
#include "stdarg.h" //JFang

//JFang @amomcu
int SerialPrintf(const char*fmt, ...); //SerialPrintf("%s\r\n",str);

/*
打印一个字符串
str不可以包含0x00，除非结尾
*/
extern void NPI_PrintString(uint8 *str);

/*
打印指定的格式的数值
参数
title,前缀字符串
value,需要显示的数值
format,需要显示的进制，十进制为10,十六进制为16
*/
extern void NPI_PrintValue(char *title, uint16 value, uint8 format);

/*******************************************************************************
*/

// 该函数延时时间为1ms， 用示波器测量过， 稍有误差， 但误差很小  --amomcu.com
void simpleBLE_Delay_1ms(int times);

/*******************************************************************************
*/



#ifdef __cplusplus
}
#endif

#endif /* _PUBLIC_H */