#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "Config.h"

#define Battery_gpio_init P0_MODE_IN_HIZ(GPIO_Pin_4)
#define ADC_channel ADC_CH12
#define FULL_VOLTAGE 12.6
#define LOW_VOLTAGE 10.5

void Battery_init();

float GET_Battery_vol();

#endif