#include "App.h"
#include "oled.h"
#include "bmp.h"
#include "EEPROM.h"

u16 electric_quantity = 0;
u16 total = 0;
u16 subtotal = 0;
u16 EEPROM_addr_sector = 0x0000;
u8 EEPROM_temp[2];
	
void task_oled() _task_ TASK_OLED
{
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
	OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	OLED_Clear();
	
	EEPROM_read_n(EEPROM_addr_sector, EEPROM_temp, 2);
	
	total = EEPROM_temp[0] + EEPROM_temp[1] * 256;
	
	while(1)
	{
		OLED_Display_GB2312_string(0, 0, "S���ӹ���������S");
		OLED_Display_GB2312_string(0, 2, "�ۼƹ��£�");
		OLED_Display_GB2312_string(0, 4, "���ι��£�");
		OLED_ShowNum(88, 2, total, 5);
		OLED_ShowNum(88, 4, subtotal, 5);
		OLED_ShowNum(0, 6, electric_quantity, 2);
		OLED_Display_GB2312_string(16, 6, "%");
		OLED_Display_GB2312_string(80, 6, "����+1");
		os_wait2(K_TMO, 80);
		OLED_Display_GB2312_string(80, 6, "      ");
		os_wait1(K_SIG);
	}
}