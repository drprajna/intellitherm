/*
JFang, 20150530
*/

#include<ioCC2540.h>
#include "stdio.h"
#include "ADS8326.h"
#define uint16      unsigned short

/**************************************************
  接口定义，移植此程序只需修改下列宏定义和延时函数
**************************************************/
//JFang
#define HIGH            1                 //高电平
#define LOW             0                 //低电平

/*#define LED1 P1_0       //定义P1.0口为LED1控制端
#define LED2 P1_1       //定义P1.1口为LED2控制端
#define LED3 P1_4       //定义P1.4口为LED3控制端
#define LED4 P0_1       //定义P0.1口为LED4控制端
*/

#define SCLK   P1_5 //clk
#define CS     P1_4
#define MISO   P1_7  //JFang, master in slave out

#define SET_OUT()   P1DIR |= 0x30;  //设置P1 IO方向,out设置IO方向为输出
#define SET_IN()    P1DIR &= 0x7F;  //设置P1 IO方向,in设备IO方向为输入

/*
 *    延时函数
 *    输入微秒
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
* 名    称: InitSPI()
* 功    能: 设置SPI总线相应的IO口
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitSPI(void)
{
    P1DIR |= 0x30;      //P1.4、P1.5定义为输出
    P1DIR &= 0x7F;      //P1.7定义为输入    
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
       
    //开始转换
    DS18B20_SendConvert();
    //延时1S
    for(i=20; i>0; i--)
      delay_nus(50000);
    DS18B20_GetTem();
    sprintf(buf, "%d", sensor_data_value[1]);
    HalLcd_HW_WriteLine(HAL_LCD_LINE_5, buf);
  }
}
#endif


