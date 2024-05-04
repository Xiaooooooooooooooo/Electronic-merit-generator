#include "Key.h"
#include "GPIO.h"

void Key_init()
{
	Key_gpio_init;
}

u8 Key_states = 0xff;
void Key_scan()
{
	if(KEY1 != KEY_STATE(1))
	{
		KEY_STATE_SW(1);
		if(KEY1)
		{
			is_key_up(1);
		}else
		{
			is_key_down(1);
		}
	}
	
	if(KEY2 != KEY_STATE(2))
	{
		KEY_STATE_SW(2);
		if(KEY2)
		{
			is_key_up(2);
		}else
		{
			is_key_down(2);
		}
	}
	
	if(KEY3 != KEY_STATE(3))
	{
		KEY_STATE_SW(3);
		if(KEY3)
		{
			is_key_up(3);
		}else
		{
			is_key_down(3);
		}
	}
}