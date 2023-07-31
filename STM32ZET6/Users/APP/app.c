/*
 * @Author: DuRuofu duruofu@qq.com
 * @Date: 2023-07-13 17-13-53
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-29 17-18-27
 * @FilePath: \MDK-ARMd:\duruofu\Project\Avoidance_Car\project\STM32ZET6\Users\APP\app.c
 * @Description: 应用层模块
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved.
 */

#include "app.h"
#define TAG "APP"

//-------------------野火上位机调参用-------------------
extern int32_t Kp;     // 比例系数
extern int32_t Ki;      // 积分系数
extern int32_t Kd;      // 微分系数
extern int32_t Cycle; // 采样周期
extern int32_t Target;  // 目标值

//-----------------------------------------------------
extern int32_t Car_Speed_A ;    // 电机实际速度（电机A）
extern int32_t Car_Speed_B ;    // 电机实际速度（电机B）


uint8_t Grayscale_Value[5] = {0}; // 五路灰度模块的值
extern uint16_t CCD_Value[128]={0};   // CCD采集的数据
extern uint8_t CCD_Zhongzhi; // GUI菜单


uint8_t CCD_Count = 0;     // CCD计数

/**
 * @description: 系统应用初始化
 * @return {*}
 */
void App_Init(void)
{
    OLED_Init();          // 0.96oled初始化
    OLED_Clear();
    Motor_Init();         // 电机初始化
    USART_IT_Config();    // 总串口接收初始化
    Encoder_Count_Init(); // 编码器计数初始化
    Yuntai_Init();        // 云台初始化

    protocol_init();      /* 协议初始化 */ 
    float pid_temp[3] = {(float)Kp, (float)Ki, (float)Kd};
    set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3); // 给通道 1 发送 P I D
    set_computer_value(SEND_TARGET_CMD, CURVES_CH1, &Target, 1); // 给通道 1 发送目标值
    set_computer_value(SEND_PERIOD_CMD, CURVES_CH1, &Cycle, 1);  // 给通道 1 发送周期值

    HAL_TIM_Base_Start_IT(&htim2); // 启动定时器4 开始数据采样,执行控制
    
}

/**
 * @description: 系统应用循环任务
 * @return {*}
 */
void App_Task(void)
{


    //receiving_process();                                                // 协议接收处理(野火上位机)
    //set_computer_value(SEND_FACT_CMD, CURVES_CH1, &Car_Speed_A, 1);     // 给通道 1 发送电机A实际值
    //set_computer_value(SEND_FACT_CMD, CURVES_CH1, &Car_Speed_B, 1);   // 给通道 1 发送电机B实际值

    //  读取灰度模块作为实际方向
    //  Grayscale_Read_Err();
    //  发送CCD数据
    
        // if (CCD_Count > 20)
        // {
            
        // CCD_Collect();// 读取CCD
        // Find_CCD_Zhongzhi(CCD_Value); //计算中值

        // DEBUG_info(TAG,"CCD_Zhongzhi = %d", CCD_Zhongzhi);
        // DEBUG_info(TAG,"CCD_ERR = %d", 64-CCD_Zhongzhi);
        
        //     CCD_Count = 0;

        // }
        // Car_PID_Ctrl(); //电机控制


    Menu_Refresh(); // 刷新菜单
}



// 定时器中断回调函数(1ms一次)
uint8_t encoder_count = 0; // 编码器计数
uint8_t LED_Heartbeat = 0; // LED心跳


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2) // 判断中断是否来自于定时器1
    {
        // 编码器测速任务
        encoder_count++;
        if (encoder_count == 10)
        {
            // 计数值清零
            encoder_count = 0;
            // 读取编码器速度
            Motor_Speed_Read();
            
        }
        // 心跳(50ms一次)
        LED_Heartbeat++;
        if (LED_Heartbeat == 30)
        {
            LED_Toggle(1);      
            Yuntai_PID();
        }

        CCD_Count++;

    }
}




//--------------------野火上位机调试改变PID参数的函数接口--------------------
/**
 * @description: 设置比例、积分、微分系数
 * @param {float} Kp 比例系数 P
 * @param {float} Ki 积分系数 i
 * @param {float} Kd 微分系数 d
 * @return {*} 无
 */
void Set_PID(int32_t kp, int32_t ki, int32_t kd)
{
    Kp = (int32_t)kp; // 设置比例系数 P
    Ki = (int32_t)ki; // 设置积分系数 I
    Kd = (int32_t)kd; // 设置微分系数 D
    DEBUG_info(TAG, "Set_PID: Kp=%u, Ki=%u, Kd=%u", Kp, Ki, Kd);
}

/**
 * @description: 设置当前的目标值
 * @param {float} temp_val
 * @return {*}
 */
void Set_PID_Target(float temp_val)
{
    DEBUG_info(TAG, "set_pid_target: %f", temp_val);
    Target = temp_val; // 设置当前的目标值
    set_computer_value(SEND_TARGET_CMD, CURVES_CH1, &Target, 1); 
}
