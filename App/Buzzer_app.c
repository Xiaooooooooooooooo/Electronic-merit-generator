#include "App.h"
#include "Buzzer.h"

u8 notes[] = {1,1,1,1,1,1,1};

u8 gap[] = {1,1,1,1,1,1,1};

u8 is_buzzer_enable = 0;

void task_buzzer() _task_ TASK_BUZZER
{
	u8 i;
	Buzzer_init();
	while(1)
	{
		if(!is_buzzer_enable)
		{
			os_wait2(K_TMO, 2);
			continue;
		}
		
		for(i = 0; i < sizeof(notes); i++)
		{
			Buzzer_play(notes[i]);
			os_wait2(K_TMO, gap[i] * 20);
			Buzzer_stop();
			os_wait2(K_TMO, 4);
		}
		os_wait2(K_TMO, 2);
	}
}