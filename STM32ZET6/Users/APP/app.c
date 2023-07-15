/*
 * @Author: DuRuofu duruofu@qq.com
 * @Date: 2023-07-13 17-13-53
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-15 17-57-38
 * @FilePath: \MDK-ARMd:\duruofu\Project\Avoidance_Car\project\STM32ZET6\Users\APP\app.c
 * @Description: 应用层模块
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved. 
 */

#include "app.h"
#define TAG "APP"

int32_t target_speed = 20.0; //目标速度
int32_t car_speed_1 = 0; // 电机1速度
int32_t car_speed_2 = 0; // 电机2速度

uint8_t Grayscale_Value[5] = {0}; // 五路灰度模块的值

/**
 * @description: 系统应用初始化
 * @return {*}
 */
void App_Init(void)
{
    OLED_Init();          // 0.96oled初始化
    Motor_Init();         // 电机初始化
    USART_IT_Config();    // 总串口接收初始化
    Encoder_Count_Init(); // 编码器计数初始化
    
    protocol_init();/* 协议初始化 */

    // 开始数据采样
    HAL_TIM_Base_Start_IT(&htim2); // 启动定时器4

    //控制电机
    Motor_Ctrl(5000, 1);
    //Motor_Ctrl(5000, 2);
    
    float pid_temp[3] = {1.2, 2.2, 3.2};
    set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3);     // 给通道 1 发送 P I D 
    
    set_computer_value(SEND_TARGET_CMD, CURVES_CH1, &target_speed, 1);  // 给通道 1 发送目标值
    
    
}

/**
 * @description: 系统应用循环任务
 * @return {*}
 */
void App_Task(void)
{
    LED_Toggle(); // LED心跳
    /* 接收数据处理 */
    receiving_process();

    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &car_speed_1, 1);     // 给通道 1 发送实际值
    
    // 显示电机速度
    OLED_ShowSignedNum(1, 1, car_speed_1, 5);
    OLED_ShowSignedNum(1, 8, car_speed_2, 5);

   //DEBUG_info(TAG,"%d,%d,%d,%d,%d",Grayscale_Value[0],Grayscale_Value[1],Grayscale_Value[2],Grayscale_Value[3],Grayscale_Value[4]);

}


// 定时器中断回调函数(1ms一次)
uint16_t encoder_count = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2) // 判断中断是否来自于定时器1
    {
        // 编码器测速任务
        encoder_count++;
        if (encoder_count == 5)
        {
            // 计数值清零
            encoder_count = 0;
            // 读取编码器速度
            Motor_Speed_Read();
        }
        //读取灰度模块
        Grayscale_Read(Grayscale_Value);
    }
}


//读取电机速度
void Motor_Speed_Read(void)
{
    // 读取编码器速度
    car_speed_1 = Encoder_Value(1);
    car_speed_2 = Encoder_Value(2);
    // 清零编码器计数值
    Encoder_Count_Clear(1);
    Encoder_Count_Clear(2);
}


// pid部分



/**
 * @description: 设置比例、积分、微分系数
 * @param {float} Kp 比例系数 P
 * @param {float} Ki 积分系数 i
 * @param {float} Kd 微分系数 d
 * @return {*} 无
 */
void Set_PID(float Kp, float Ki, float Kd)
{
    DEBUG_info(TAG, "Set_PID: Kp=%f, Ki=%f, Kd=%f", Kp, Ki, Kd);
//    ?= p;    // 设置比例系数 P
//    ?= i;    // 设置积分系数 I
//    ?= d;    // 设置微分系数 D
}




/**
 * @description: 设置当前的目标值
 * @param {float} temp_val
 * @return {*}
 */
void Set_PID_Target(float temp_val)
{
  DEBUG_info(TAG, "set_pid_target: %f", temp_val);
  target_speed = temp_val;    // 设置当前的目标值
}




// /**
//  * @description: 小车PID总输出
//  * @return {*}
//  */
// void Car_PID_Ctrl(void)
// {
//     // 直立环
//     PWM_Upright = PID_Upright(pitch, gyroy);
//     // 速度环
//     PWM_Speed = PID_Speed(car_speed_1, car_speed_2);

//     // 转向环

//     // 最终输出PWM
//     PWM_Output_1 = PWM_Upright+PWM_Speed;
//     PWM_Output_2 = PWM_Upright+PWM_Speed;

//     // 限幅
//     if (PWM_Output_1 >= PWM_MAX)
//     {
//         PWM_Output_1 = PWM_MAX;
//     }
//     if (PWM_Output_1 <= -PWM_MAX)
//     {
//         PWM_Output_1 = -PWM_MAX;
//     }
//     if (PWM_Output_2 >= PWM_MAX)
//     {
//         PWM_Output_2 = PWM_MAX;
//     }
//     if (PWM_Output_2 <= -PWM_MAX)
//     {
//         PWM_Output_2 = -PWM_MAX;
//     }
//     if ((pitch >= 80) || (pitch <= -80))
//     {
//         PWM_Output_1 = 0;
//         PWM_Output_2 = 0;
//     }
//     // 作用到电机
//     Motor_Ctrl(PWM_Output_1, 1); // 作用到电机
//     Motor_Ctrl(PWM_Output_2, 2); // 作用到电机
// }

