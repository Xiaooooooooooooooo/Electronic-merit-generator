#include "Battery.h"
#include "GPIO.h"
#include "ADC.h"
#include "NVIC.h"
#include "Switch.h"

/******************* ADC���ú��� *******************/
void ADC_config()
{
	ADC_InitTypeDef		ADC_InitStructure;		//�ṹ����

	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//��ʼ��
	ADC_PowerControl(ENABLE);				//ADC��Դ����, ENABLE��DISABLE
	NVIC_ADC_Init(DISABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

void Battery_init()
{
	Battery_gpio_init;
	ADC_config();
}

float GET_Battery_vol()
{
	u16 ADC_value = Get_ADCResult(ADC_channel); // chn: ADC_CH0, ADC_CH1, ADC_CH2 .... ADC_CH15
	float vol = 6 * 2.5 * ADC_value / 4095;
	return vol;
}