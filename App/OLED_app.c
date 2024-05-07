#include "App.h"
#include "oled.h"
#include "bmp.h"


void task_oled() _task_ TASK_OLED
{
	u16 total = 50;
	u16 subtotal = 200;
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
	OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	OLED_Clear();
	
	while(1)
	{
		OLED_Display_GB2312_string(0, 0, "S���ӹ���������S");
		OLED_Display_GB2312_string(0, 2, "�ۼƹ��£�");
		OLED_Display_GB2312_string(0, 4, "��ǰ���£�");
		OLED_ShowNum(80, 2, total, 5);
		OLED_ShowNum(80, 4, subtotal, 5);
		OLED_ShowNum(0, 6, electric_quantity, 2);
		OLED_Display_GB2312_string(16, 6, "%");
		OLED_Display_GB2312_string(80, 6, "����+1");
		os_wait2(K_TMO, 100);
	}
}