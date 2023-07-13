/*
 * @Author: DuRuofu duruofu@qq.com
 * @Date: 2023-07-13 16-08-26
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-13 16-22-08
 * @FilePath: \MDK-ARMd:\duruofu\Project\Avoidance_Car\project\STM32ZET6\Users\Grayscale\Grayscale.c
 * @Description: 五路灰度模块
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved. 
 */
#include "Grayscale.h"



// 不使用使用CubeMX自动生成的宏定义，就使用下面的：
// #define Follow_1_Pin GPIO_PIN_4
// #define Follow_1_GPIO_Port GPIOB
// #define Follow_2_Pin GPIO_PIN_6
// #define Follow_2_GPIO_Port GPIOB
// #define Follow_3_Pin GPIO_PIN_7
// #define Follow_3_GPIO_Port GPIOB
// #define Follow_4_Pin GPIO_PIN_8
// #define Follow_4_GPIO_Port GPIOB
// #define Follow_5_Pin GPIO_PIN_9
// #define Follow_5_GPIO_Port GPIOB

/**
 * @description: 五路灰度模块初始化
 * @return {*}
 */
void Grayscale_Init(void)
{
    //引脚初始化
    //---------使用CubeMX就不用写这些了---------
         //引脚初始化代码....

}


/**
 * @description: 读取五路灰度模块的值
 * @return {*}
 */
uint8_t Grayscale_Read(uint8_t *Grayscale_Value)
{
    /* 读取循迹模块的状态 */
    Grayscale_Value[0] = HAL_GPIO_ReadPin(Follow_1_GPIO_Port, Follow_1_Pin);
    Grayscale_Value[2] = HAL_GPIO_ReadPin(Follow_2_GPIO_Port, Follow_2_Pin);
    Grayscale_Value[3] = HAL_GPIO_ReadPin(Follow_3_GPIO_Port, Follow_3_Pin);
    Grayscale_Value[4] = HAL_GPIO_ReadPin(Follow_4_GPIO_Port, Follow_4_Pin);
    Grayscale_Value[5] = HAL_GPIO_ReadPin(Follow_5_GPIO_Port, Follow_5_Pin);
}