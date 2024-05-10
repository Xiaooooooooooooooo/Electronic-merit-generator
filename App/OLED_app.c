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
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
	OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	
	EEPROM_read_n(EEPROM_addr_sector, EEPROM_temp, 4);
	
	if((EEPROM_temp[0] + (EEPROM_temp[1] * 256) + (EEPROM_temp[2] * 65536UL) + (EEPROM_temp[3] * 16777216UL)) > 999999) total = 0;
	else total = EEPROM_temp[0] + (EEPROM_temp[1] * 256) + (EEPROM_temp[2] * 65536UL) + (EEPROM_temp[3] * 16777216UL);
	
	while(1)
	{
		if(total == 1000000)
		{
			OLED_Display_GB2312_string(8, 0, "���ӹ���������");
			OLED_Display_GB2312_string(0, 2, "!��ϲ�������ֻ�!");
			OLED_Display_GB2312_string(24, 4, "<����Բ��>");
			OLED_Display_GB2312_string(0, 6, "�����ʼ�µ��ֻ�");
			os_wait2(K_TMO, 2);
			continue;
		}
		
		if(total > 999999)
		{
			total = 0;
			subtotal = 0;
		}
		
		OLED_Clear();
		OLED_Display_GB2312_string(8, 0, "���ӹ���������");
		OLED_Display_GB2312_string(0, 2, "�ۼƹ��£�");
		OLED_Display_GB2312_string(0, 4, "���ι��£�");
		OLED_ShowNum(80, 2, total, 6);
		OLED_ShowNum(80, 4, subtotal, 6);
		OLED_ShowNum(0, 6, electric_quantity, 2);
		OLED_Display_GB2312_string(16, 6, "%");
		os_wait1(K_SIG);
		OLED_Display_GB2312_string(80, 6, "����+1");
		os_wait2(K_TMO, 70);
		OLED_Clear();
	}
}