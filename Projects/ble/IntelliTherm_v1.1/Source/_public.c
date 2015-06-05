#include "_public.h"

//JFang
int SerialPrintf(const char*fmt, ...)
{
    uint32  ulLen;
    va_list ap;

    char *pBuf = (char*)osal_mem_alloc(128);  // 开辟缓冲区
    va_start(ap, fmt);
    ulLen = vsprintf(pBuf, fmt, ap);        // 用虚拟打印函数实现
    va_end(ap);

    HalUARTWrite(HAL_UART_PORT_0, (uint8*)pBuf, ulLen); // 从串口0输出
    osal_mem_free(pBuf);    // 释放内存空间
    return ulLen;
}


/*
打印一个字符串
str不可以包含0x00，除非结尾
*/
void NPI_PrintString(uint8 *str)
{
    NPI_WriteTransport(str, osal_strlen((char*)str));
}
/*
打印指定的格式的数值
参数
title,前缀字符串
value,需要显示的数值
format,需要显示的进制，十进制为10,十六进制为16
*/
void NPI_PrintValue(char *title, uint16 value, uint8 format)
{
  uint8 tmpLen;
  uint8 buf[128];
  uint32 err;

  tmpLen = (uint8)osal_strlen( (char*)title );
  osal_memcpy( buf, title, tmpLen );
  buf[tmpLen] = ' ';
  err = (uint32)(value);
  _ltoa( err, &buf[tmpLen+1], format );
  NPI_PrintString(buf);		
}

// 该函数延时时间为1ms， 用示波器测量过， 稍有误差， 但误差很小  --amomcu.com
void NPI_Delay_1ms(int times)
{
  while(times--)
  {
      int i=0;
      for(i=1500;i>0;i--)
      {
    	  asm("nop");
      }
  }
}