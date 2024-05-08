#include "App.h"
#include "Servo.h"
#include "Key.h"

u8 is_Servo_aoto = 0;

void task_servo() _task_ TASK_SERVO
{
	while(1)
	{
		if(!is_Servo_aoto)
		{
			os_wait2(K_TMO, 2);
			continue;
		}
		
		Servo_run(45);
		os_wait2(K_TMO, 100);
		Servo_run(135);
		total++; subtotal++;
		os_send_signal(TASK_OLED);
		os_wait2(K_TMO, 100);
	}
}