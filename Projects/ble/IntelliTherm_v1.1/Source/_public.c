#include "_public.h"

//JFang
int SerialPrintf(const char*fmt, ...)
{
    uint32  ulLen;
    va_list ap;

    char *pBuf = (char*)osal_mem_alloc(128);  // ���ٻ�����
    va_start(ap, fmt);
    ulLen = vsprintf(pBuf, fmt, ap);        // �������ӡ����ʵ��
    va_end(ap);

    HalUARTWrite(HAL_UART_PORT_0, (uint8*)pBuf, ulLen); // �Ӵ���0���
    osal_mem_free(pBuf);    // �ͷ��ڴ�ռ�
    return ulLen;
}


/*
��ӡһ���ַ���
str�����԰���0x00�����ǽ�β
*/
void NPI_PrintString(uint8 *str)
{
    NPI_WriteTransport(str, osal_strlen((char*)str));
}
/*
��ӡָ���ĸ�ʽ����ֵ
����
title,ǰ׺�ַ���
value,��Ҫ��ʾ����ֵ
format,��Ҫ��ʾ�Ľ��ƣ�ʮ����Ϊ10,ʮ������Ϊ16
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

// �ú�����ʱʱ��Ϊ1ms�� ��ʾ������������ ������ ������С  --amomcu.com
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