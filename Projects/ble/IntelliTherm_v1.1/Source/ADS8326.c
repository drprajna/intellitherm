/*
JFang, 20150530
*/

#include<ioCC2540.h>
#include "stdio.h"
#include "ADS8326.h"
#define uint16      unsigned short

/**************************************************
  �ӿڶ��壬��ֲ�˳���ֻ���޸����к궨�����ʱ����
**************************************************/
//JFang
#define HIGH            1                 //�ߵ�ƽ
#define LOW             0                 //�͵�ƽ

/*#define LED1 P1_0       //����P1.0��ΪLED1���ƶ�
#define LED2 P1_1       //����P1.1��ΪLED2���ƶ�
#define LED3 P1_4       //����P1.4��ΪLED3���ƶ�
#define LED4 P0_1       //����P0.1��ΪLED4���ƶ�
*/

#define SCLK   P1_5 //clk
#define CS     P1_4
#define MISO   P1_7  //JFang, master in slave out

#define SET_OUT()   P1DIR |= 0x30;  //����P1 IO����,out����IO����Ϊ���
#define SET_IN()    P1DIR &= 0x7F;  //����P1 IO����,in�豸IO����Ϊ����

/*
 *    ��ʱ����
 *    ����΢��
 */
void delay_nus(uint16 timeout)
{
    while (timeout--)
    {
        asm("NOP");
        asm("NOP");
        asm("NOP");
    }
}

void delay1(int t1,int t2)
{
   unsigned int i,j;               
   for(i=0;i<t1;i++)
      for(j=0;j<t2;j++);

}


/****************************************************************************
* ��    ��: InitSPI()
* ��    ��: ����SPI������Ӧ��IO��
* ��ڲ���: ��
* ���ڲ���: ��
****************************************************************************/
void InitSPI(void)
{
    P1DIR |= 0x30;      //P1.4��P1.5����Ϊ���
    P1DIR &= 0x7F;      //P1.7����Ϊ����    
}

unsigned int ADS8326_Read()
{
    unsigned int adc_read = 0;   // result to return
    int i;
    InitSPI();
    
    CS=HIGH;
    delay1(1,1);
    CS=LOW;
    delay1(1,1);
    
    //JFang, sample, 6 clks
    for(i=0;i<6;i++)
    {
      SCLK=LOW;
      delay1(1,1);
      SCLK=HIGH;
      delay1(1,1);
    }
    
    //JFang, conversion
    for(i=0;i<16;i++)
    {
      SCLK=LOW;
      delay1(1,1);
      SCLK=HIGH;   //SCLK=1; 
      delay1(1,1);
      adc_read=(adc_read<<1)+MISO;
    }
    CS=HIGH;
    return adc_read;
}





float ADS8326_ReadMain(void)
{
    unsigned int result=0;
    float ft=0;
   result=ADS8326_Read();
   ft=result/1000;
    return ft;
}


#if  0
int main()
{
  HAL_BOARD_INIT();
  HalLcd_HW_Init();
  
  HalLcd_HW_WriteLine(HAL_LCD_LINE_1, "      CC254xEM");
  HalLcd_HW_WriteLine(HAL_LCD_LINE_3, "-->DS18B20_TEST"); 
  HalLcd_HW_WriteLine(HAL_LCD_LINE_4, "Current Temp:");

  uint8 i;
  uint8 buf[10];
  while(1){
       
    //��ʼת��
    DS18B20_SendConvert();
    //��ʱ1S
    for(i=20; i>0; i--)
      delay_nus(50000);
    DS18B20_GetTem();
    sprintf(buf, "%d", sensor_data_value[1]);
    HalLcd_HW_WriteLine(HAL_LCD_LINE_5, buf);
  }
}
#endif


