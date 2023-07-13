/*
 * @Author: DuRuofu duruofu@qq.com
 * @Date: 2023-07-13 17-13-53
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-13 20-40-57
 * @FilePath: \MDK-ARMd:\duruofu\Project\Avoidance_Car\project\STM32ZET6\Users\Encoder\encoder.c
 * @Description: 编码器模块
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved. 
 */

#include "encoder.h"

//编码器计数初始化
void Encoder_Count_Init(void)
{
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

//编码器数据读取
int16_t Encoder_Value(uint8_t n)
{
    if (n == 1)
    {
        return (int16_t)(__HAL_TIM_GET_COUNTER(&htim3));
    }
    else if (n == 2)
    {
        return (int16_t)(__HAL_TIM_GET_COUNTER(&htim4));
    }
    else
    {
        return 0;
    }
}

//编码器清零
void Encoder_Count_Clear(uint8_t n)
{
    if (n == 1)
    {
        __HAL_TIM_SET_COUNTER(&htim3, 0);
    }
    else if (n == 2)
    {
        __HAL_TIM_SET_COUNTER(&htim4, 0);
    }
}


