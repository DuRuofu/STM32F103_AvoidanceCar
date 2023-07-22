/*
 * @Author: DuRuofu duruofu@qq.com
 * @Date: 2023-07-13 17-13-53
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-18 17-30-08
 * @FilePath: \MDK-ARMd:\duruofu\Project\Avoidance_Car\project\STM32ZET6\Users\USART\serial_it_config.c
 * @Description: 串口接收中断配置(总)
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved. 
 */

#include "serial_it_config.h"

/**
 * @description: 串口接收中断初始化(总)
 * @return {*}Debug_Init
 */
void USART_IT_Config(void)
{
    //串口1接收中断初始化
    Debug_Init();
    //串口2接收中断初始化
    USART2_Init();
    //串口3接收中断初始化
    USART3_Init();
}

//串口接收完成回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        UART1_RxCpltCallback(huart);
    }
    else if(huart->Instance == USART2)
    {
        //UART2_RxCpltCallback();
        //串口2的接收逻辑依然在stm32f1xx_it.c中（待修改）
    }
    else if(huart->Instance == USART3)
    {
        //UART2_RxCpltCallback();
        UART3_RxCpltCallback(huart);
    }
    }


//错误回调  
 void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)   
{       
    if(huart->Instance == USART1)
    {
        UART1_ErrorCallback(huart);
    }
    else if(huart->Instance == USART2)
    {
        UART2_ErrorCallback(huart);
    }
    else if(huart->Instance == USART3)
    {
        UART3_ErrorCallback(huart);
    } 
}

