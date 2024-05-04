#include "buzzer.h"
#include "STC8H_PWM.h"
#include "NVIC.h"
#include "Switch.h"

static void PWM_config()
{
    PWMx_InitDefine PWMx_InitStructure;

    // 配置PWM5
    PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;           // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty = (MAIN_Fosc / 1000) * 0.5; // PWM占空比时间, 0~Period
    PWMx_InitStructure.PWM_EnoSelect = ENO5P;                // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM5, &PWMx_InitStructure);            // 初始化PWM,  PWMA,PWMB

    // 配置PWMB
    PWMx_InitStructure.PWM_Period = (MAIN_Fosc / 1000) - 1; // 周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;                    // 死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable = DISABLE;         // 主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable = DISABLE;            // 使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);           // 初始化PWM通用寄存器,  PWMA,PWMB

    // 切换PWM通道
    PWM5_SW(PWM5_SW_P00); // PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74

    // 初始化PWMB的中断
    NVIC_PWM_Init(PWMB, DISABLE, Priority_0);
}

void PWM_play(u16 Hz)
{
    PWMx_InitDefine PWMx_Hz;
    PWMx_Hz.PWM_Period = (MAIN_Fosc / Hz) - 1;
    PWMx_Hz.PWM_MainOutEnable = ENABLE;
    PWMx_Hz.PWM_CEN_Enable = ENABLE;
    PWM_Configuration(PWMB, &PWMx_Hz);
}

void PWM_stop()
{
    PWMx_InitDefine PWMx_stop;
    PWMx_stop.PWM_MainOutEnable = DISABLE;
    PWMx_stop.PWM_CEN_Enable = DISABLE;
    PWM_Configuration(PWMB, &PWMx_stop);
}

void Buzzer_init()
{
    PWM_config();
}

u16 hz[] = {440, 523, 587, 659, 698, 784, 880, 988, 1047};

void Buzzer_play(u8 NOTE)
{
    PWM_play(hz[NOTE]);
}

void Buzzer_stop()
{
    PWM_stop();
}