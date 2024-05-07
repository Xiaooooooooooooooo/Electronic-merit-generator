#include "App.h"
#include "Key.h"
#include "GPIO.h"
#include "Servo.h"
#include "Buzzer.h"
#include "EEPROM.h"

void is_key_up(u8 key)
{
	switch(key)
	{
		case 1:
			printf("KEY1 up");
			P54 = 0;
			break;
		case 2:
			printf("KEY2 up"); break;
		case 3:
			printf("KEY3 up"); break;
		default: break;
	}
}

void is_key_down(u8 key)
{
	switch(key)
	{
		case 1:
			printf("KEY1 down"); 
			P54 = 1;
			break;
		case 2:
			printf("KEY2 down");
			is_Servo_aoto = !is_Servo_aoto;
			is_Buzzer_play = !is_Buzzer_play;
			break;
		case 3:
			printf("KEY3 down"); break;
		default: break;
	}
}

void task_key() _task_ TASK_KEY
{
	Key_init();
	Servo_init();
	Buzzer_init();
	while(1)
	{
		Key_scan();
		os_wait2(K_TMO, 2);
	}
}