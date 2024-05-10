#include "App.h"
#include "Key.h"
#include "Servo.h"
#include "Buzzer.h"
#include "EEPROM.h"

void is_key_up(u8 key)
{
	switch(key)
	{
		case 1:
//			printf("KEY1 up");
			LED = 0;
			if(!is_Servo_aoto) Servo_run(45);
			if(!is_Buzzer_play) Buzzer_stop();
			break;
		case 2:
//			printf("KEY2 up");
			break;
		case 3:
//			printf("KEY3 up");
			break;
		default: break;
	}
}

void is_key_down(u8 key)
{
	switch(key)
	{
		case 1:
//			printf("KEY1 down");
			LED = 1;
			if(!is_Servo_aoto) Servo_run(135);
			if(!is_Buzzer_play) Buzzer_play(1);
			if(total == 1000000) os_send_signal(TASK_BUZZER1);
			total++; subtotal++;
			os_send_signal(TASK_OLED);
			break;
		case 2:
//			printf("KEY2 down");
			if(total == 1000000) os_send_signal(TASK_BUZZER1);
			is_Servo_aoto = !is_Servo_aoto;
			is_Buzzer_play = !is_Buzzer_play;
			break;
		case 3:
//			printf("KEY3 down");
			EEPROM_temp[0] = total % 256; EEPROM_temp[1] = (total % (65536UL)) / 256;
			EEPROM_temp[2] = (total % (16777216UL)) / (65536UL); EEPROM_temp[3] = total / (16777216UL);
			EEPROM_SectorErase(EEPROM_addr_sector);
			EEPROM_write_n(EEPROM_addr_sector, EEPROM_temp, 4);
			break;
		default: break;
	}
}

void task_key() _task_ TASK_KEY
{
	Key_init();
	Servo_init();
	Buzzer_init();
	LED = 0;
	while(1)
	{
		Key_scan();
		os_wait2(K_TMO, 2);
	}
}