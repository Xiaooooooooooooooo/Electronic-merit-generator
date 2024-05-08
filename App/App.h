#ifndef __APP_H__
#define __APP_H__

#include "Config.h"

#define TASK_KEY 1
#define TASK_BUZZER 2
#define TASK_OLED 3
#define TASK_BATTERY 4
#define TASK_SERVO 5

#define LED P54

extern u8 is_Servo_aoto;
extern u8 is_Buzzer_play;
extern u16 electric_quantity;
extern u32 total;
extern u32 subtotal;
extern u16 EEPROM_addr_sector;
extern u8 EEPROM_temp[4];

#endif