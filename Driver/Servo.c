#include "Servo.h"
#include "STC8H_PWM.h"
#include "NVIC.h"
#include "Switch.h"

#define Prescaler 10

#define PREQ 50

#define PERIOD (MAIN_Fosc / Prescaler / PREQ)
PWMx_Duty dutyA;
static void	PWM_config(void)
{
    PWMx_InitDefine		PWMx_InitStructure;
	
	// 配置PWM3
	PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    		= dutyA.PWM3_Duty;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect    = ENO3P;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM3, &PWMx_InitStructure);			//初始化PWM

	// 配置PWMA
    PWMx_InitStructure.PWM_Period   = PERIOD - 1;			//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

	PWMA_Prescaler(Prescaler - 1);
	
	// 切换PWM通道
	PWM3_SW(PWM3_SW_P14_P15);			//PWM3_SW_P14_P15,PWM3_SW_P24_P25,PWM3_SW_P64_P65
	// 初始化PWMA的中断
    NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}

void Servo_init()
{
	PWM_config();
}

void Servo_run(u8 angle)
{
	dutyA.PWM3_Duty =PERIOD * (angle * 20 / 180.0 + 5) / 200;
	UpdatePwm(PWM3, &dutyA);
}