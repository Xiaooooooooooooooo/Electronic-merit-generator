#ifndef __KEY_H__
#define __KEY_H__

#include "Config.h"

#define Key_gpio_init P5_MODE_IO_PU(GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3)

#define KEY1 P51
#define KEY2 P52
#define KEY3 P53

#define KEY_STATE(pos) ((Key_states >> pos) & 1)
#define KEY_STATE_SW(pos) Key_states ^= (1 << pos)

void Key_init();

void Key_scan();

extern void is_key_up(u8);
extern void is_key_down(u8);

#endif