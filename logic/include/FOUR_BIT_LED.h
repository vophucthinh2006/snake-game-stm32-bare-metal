#ifndef __FOUR_BIT_LED_H
#define __FOUR_BIT_LED_H
#include <stdint.h>
#include "GPIO.h"

typedef enum {
	ZERO  = 0b11000000,
	ONE   = 0b11111001,
	TWO   = 0b10100100,
	THREE = 0b10110000,
	FOUR  = 0b10011001,
	FIVE  = 0b10010010,
	SIX   = 0b10000010,
	SEVEN = 0b11111000,
	EIGHT = 0b10000000,
	NINE  = 0b10010000,
	A     = 0b10001100,
	B     = 0b10111111,
	C     = 0b11000110,
	D     = 0b10100001,
	E     = 0b10000110,
	F     = 0b11111111
}FOUR_BIT_NUMBER_t;

/*
		BIT_0
	BIT_5	BIT_1
		BIT6
	BIT_4	BIT_2
		BIT_3		BIT_7
*/

void FOUR_BIT_LED_Config(
		GPIO_PORT_t port,
        uint8_t latch_pin,
		uint8_t clock_pin,
		uint8_t data_pin
		);

void FOUR_BIT_LED_Send16(uint16_t data);

void FOUR_BIT_LED_Display(
		uint8_t digit1,
		uint8_t digit2,
	    uint8_t digit3,
		uint8_t digit4
		);
void FOUR_BIT_LED_Scan(
		uint8_t digit1,
		uint8_t digit2,
		uint8_t digit3,
		uint8_t digit4
		);

#endif
VÉDV
