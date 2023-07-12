#include "app.h"

int32_t car_speed_1 = 0; // 电机1速度
int32_t car_speed_2 = 0; // 电机2速度

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


    // 开始数据采样
    HAL_TIM_Base_Start_IT(&htim4); // 启动定时器4

}

/**
 * @description: 系统应用循环任务
 * @return {*}
 */
void App_Task(void)
{
    LED_Toggle(); // 测试LED
    // HAL_Delay(100);
    // 测试串口
    // 显示电机速度
    OLED_ShowSignedNum(1, 1, car_speed_1, 5);
    OLED_ShowSignedNum(1, 8, car_speed_2, 5);
    HAL_Delay(50);
}


// 定时器中断回调函数(1ms一次)
uint16_t encoder_count = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim1) // 判断中断是否来自于定时器1
    {
        // // 编码器测速任务
        // encoder_count++;
        // if (encoder_count == 5)
        // {
        //     // 计数值清零
        //     encoder_count = 0;
        //     // 读取编码器速度
        //     Motor_Speed_Read();
        // }
    }
}




//读取电机速度
void Motor_Speed_Read(void)
{
    // 读取编码器速度
    car_speed_1 = Encoder_Value(1);
    car_speed_2 = Encoder_Value(2);
    // 放大10倍
    car_speed_1 = car_speed_1 * 10;
    car_speed_2 = car_speed_2 * 10;
    // 清零编码器计数值
    Encoder_Count_Clear(1);
    Encoder_Count_Clear(2);
}

// pid部分



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