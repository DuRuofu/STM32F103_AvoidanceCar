#include "ccd.h"


//CLK和SI的宏定义，需要在CUbeMX中将引脚的用户标签命名为CCD_CLK和CCD_SI
#define CCD_CLK_H HAL_GPIO_WritePin(CCD_CLK_GPIO_Port, CCD_CLK_Pin, GPIO_PIN_SET);
#define CCD_CLK_L HAL_GPIO_WritePin(CCD_CLK_GPIO_Port, CCD_CLK_Pin, GPIO_PIN_RESET);
#define CCD_SI_H HAL_GPIO_WritePin(CCD_SI_GPIO_Port, CCD_SI_Pin, GPIO_PIN_SET);
#define CCD_SI_L HAL_GPIO_WritePin(CCD_SI_GPIO_Port, CCD_SI_Pin, GPIO_PIN_RESET);


extern uint16_t CCD_Value[128];


//微秒延时
void delay_us(uint32_t nus)
{
 uint32_t temp;
 SysTick->LOAD = 9*nus;
 SysTick->VAL=0X00;//清空计数器
 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
 do
 {
  temp=SysTick->CTRL;//读取当前倒计数值
 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
     SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
}


uint16_t Get_ADC_Value(void)
{
    HAL_ADC_Start(&hadc1); //启动ADC
    HAL_ADC_PollForConversion(&hadc1, 50); //等待转换完成，50为最大等待时间
    return HAL_ADC_GetValue(&hadc1); //返回最近一次ADC1规则组的转换结果
}

//CCD一个周期的采集
void CCD_Collect(void)
{
    CCD_SI_H; //SI=1
    CCD_CLK_L; //CLK=0
    delay_us(20); //延时1us

    CCD_CLK_H; //CLK=1
    CCD_SI_L; //SI=0
    //开始采集
    for (uint8_t i = 0; i < 128; i++)
    {
        delay_us(1);//曝光时间
        CCD_CLK_L; //CLK=0
        CCD_Value[i] = Get_ADC_Value()/32; //获取ADC值
        CCD_CLK_H; //CLK=1
    }
    CCD_CLK_L;
    CCD_CLK_H;
}


