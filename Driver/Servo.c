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
	
	// ����PWM3
	PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    		= dutyA.PWM3_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect    = ENO3P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM3, &PWMx_InitStructure);			//��ʼ��PWM

	// ����PWMA
    PWMx_InitStructure.PWM_Period   = PERIOD - 1;			//����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//��������������, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

	PWMA_Prescaler(Prescaler - 1);
	
	// �л�PWMͨ��
	PWM3_SW(PWM3_SW_P14_P15);			//PWM3_SW_P14_P15,PWM3_SW_P24_P25,PWM3_SW_P64_P65
	// ��ʼ��PWMA���ж�
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