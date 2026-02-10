#ifndef __OLED_H
#define __OLED_H
#include <stdint.h>
#include "I2C.h"
#include "SH1106.h"
#include "bitmap.h"

#define oled_x           128
#define oled_y           64

//COLOR
typedef enum{
	WHITE = 1,
	BLACK = 0
}OLED_COLOR_t;

extern uint8_t OLED_BYTE[oled_x * (oled_y / 8)];

void OLED_Init(void);

void OLED_Set_Pixel(uint8_t x, uint8_t y, OLED_COLOR_t color);
void OLED_Set_All(void);
void OLED_Clear_All(void);
void OLED_Update_Screen(void);
void OLED_Update_Page(uint8_t page);

#endif

vsdac
