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
			if(!is_Servo_aoto) Servo_run(45);
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
			if(!is_Servo_aoto) Servo_run(135);
			total++; subtotal++;
			os_send_signal(TASK_OLED);
			break;
		case 2:
			printf("KEY2 down");
			is_Servo_aoto = !is_Servo_aoto;
			is_Buzzer_play = !is_Buzzer_play;
			break;
		case 3:
			printf("KEY3 down"); 
			EEPROM_temp[0] = total % 256; EEPROM_temp[1] = total / 256;
			EEPROM_SectorErase(EEPROM_addr_sector);
			EEPROM_write_n(EEPROM_addr_sector, EEPROM_temp, 2);
			break;
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