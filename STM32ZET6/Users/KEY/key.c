#include "key.h"

#include "led.h"

#define KEY1_Pin KEY_1_Pin
#define KEY2_Pin KEY_2_Pin


/**
 * @description: 按键初始化 (使用CubeMX自动生成的宏定义，就不用写这个函数了)
 * @return {*}
 */
void Key_Init(void)
{

}

void Key_1_Callback(void)
{
    // 按键1按下的处理代码
    LED_Toggle(2);
}


void Key_2_Callback(void)
{
    // 按键2按下的处理代码
    LED_Toggle(2);
}




//
/**
 * @description: 按键检测，外部中断回调函数
 * @param {uint16_t} GPIO_Pin
 * @return {*}
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(GPIO_Pin);
    /* NOTE: This function Should not be modified, when the callback is needed,
            the HAL_GPIO_EXTI_Callback could be implemented in the user file
    */
    // 按键按下
    if(GPIO_Pin == KEY1_Pin)
    {
        // 按键1按下的处理代码
        Key_1_Callback();
    }
    else if(GPIO_Pin == KEY2_Pin)
    {
        // 按键2按下的处理代码
        Key_2_Callback();
    }
}



