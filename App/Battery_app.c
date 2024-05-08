#include "App.h"
#include "Battery.h"

void task_battery() _task_ TASK_BATTERY
{
	float vol;
	
	Battery_init();
	
	while(1)
	{
		vol = GET_Battery_vol();
		electric_quantity = (vol - LOW_VOLTAGE) * 100 / (FULL_VOLTAGE - LOW_VOLTAGE);
		printf("电池电压：%.3f V \r\n", vol);
		printf("剩余电量：%d %% \r\n", electric_quantity);
		os_wait2(K_TMO, 200);
		os_wait2(K_TMO, 200);
		os_wait2(K_TMO, 200);
	}
}