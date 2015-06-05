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
��ӡһ���ַ���
str�����԰���0x00�����ǽ�β
*/
extern void NPI_PrintString(uint8 *str);

/*
��ӡָ���ĸ�ʽ����ֵ
����
title,ǰ׺�ַ���
value,��Ҫ��ʾ����ֵ
format,��Ҫ��ʾ�Ľ��ƣ�ʮ����Ϊ10,ʮ������Ϊ16
*/
extern void NPI_PrintValue(char *title, uint16 value, uint8 format);

/*******************************************************************************
*/

// �ú�����ʱʱ��Ϊ1ms�� ��ʾ������������ ������ ������С  --amomcu.com
void simpleBLE_Delay_1ms(int times);

/*******************************************************************************
*/



#ifdef __cplusplus
}
#endif

#endif /* _PUBLIC_H */