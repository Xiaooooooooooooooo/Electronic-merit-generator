#include "App.h"
#include "oled.h"
#include "bmp.h"
#include "EEPROM.h"

u8 electric_quantity = 0;
u32 total = 0;
u32 subtotal = 0;
u16 EEPROM_addr_sector = 0x0000;
u8 EEPROM_temp[4];
	
void task_oled() _task_ TASK_OLED
{
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
	OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	
	EEPROM_read_n(EEPROM_addr_sector, EEPROM_temp, 4);
	
	if((EEPROM_temp[0] + (EEPROM_temp[1] * 256) + (EEPROM_temp[2] * 65536UL) + (EEPROM_temp[3] * 16777216UL)) > 999999) total = 0;
	else total = EEPROM_temp[0] + (EEPROM_temp[1] * 256) + (EEPROM_temp[2] * 65536UL) + (EEPROM_temp[3] * 16777216UL);
	
	while(1)
	{
		if(total == 1000000)
		{
			OLED_Display_GB2312_string(8, 0, "电子功德生成器");
			OLED_Display_GB2312_string(0, 2, "!恭喜您本次轮回!");
			OLED_Display_GB2312_string(24, 4, "<功德圆满>");
			OLED_Display_GB2312_string(0, 6, "点击开始新的轮回");
			os_wait2(K_TMO, 2);
			continue;
		}
		
		if(total > 999999)
		{
			total = 0;
			subtotal = 0;
		}
		
		OLED_Clear();
		OLED_Display_GB2312_string(8, 0, "电子功德生成器");
		OLED_Display_GB2312_string(0, 2, "累计功德：");
		OLED_Display_GB2312_string(0, 4, "本次功德：");
		OLED_ShowNum(80, 2, total, 6);
		OLED_ShowNum(80, 4, subtotal, 6);
		OLED_ShowNum(0, 6, electric_quantity, 2);
		OLED_Display_GB2312_string(16, 6, "%");
		os_wait1(K_SIG);
		OLED_Display_GB2312_string(80, 6, "功德+1");
		os_wait2(K_TMO, 70);
		OLED_Clear();
	}
}