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
			if(KEY1)
			{
				Servo_run(45);
			}else
			{
				Servo_run(135);
			}
			os_wait2(K_TMO, 2);
			continue;
		}
		
		Servo_run(45);
		os_wait2(K_TMO, 100);
		Servo_run(135);
		os_wait2(K_TMO, 100);
	}
}