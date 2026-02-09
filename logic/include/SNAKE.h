#ifndef __SNAKE_H
#define __SNAKE_H
#include <stdio.h>
#include "ADC.h"
#include "EXTI.h"
#include "TIM.h"
#include "FOUR_BIT_LED.h"
#include "OLED.h"

#define block_size       4
#define game_width       (oled_x / block_size)
#define game_height      (oled_y / block_size)
#define snake_max_length ((game_width - 2) * (game_height - 2))

//SNAKE
typedef struct{
	uint8_t x;
	uint8_t y;
}SNAKE_BLOCK_t;

//DIRECTION
typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT
}SNAKE_DIRECTION_t;

//SNAKE'S EATING / FOOD'S SPAWDING STATUS CHECKING
typedef enum{
	EATEN,
	ON,
	NONE
}STATUS_t;

typedef enum{
	SNAKE_STATE_LOBBY,
	SNAKE_STATE_START,
	SNAKE_STATE_PLAY,
	SNAKE_STATE_PAUSE,
	SNAKE_STATE_END
}SNAKE_STATE_t;

extern volatile uint8_t snake_tick_count;
extern volatile uint8_t snake_tick;
extern volatile uint8_t button_count;
extern volatile uint8_t button_stable;
extern volatile uint8_t button_pressed;
extern volatile uint8_t button_start;
extern volatile uint8_t button_pause;
extern SNAKE_STATE_t snake_state;
extern SNAKE_BLOCK_t snake[snake_max_length];
extern uint16_t snake_length;
extern SNAKE_DIRECTION_t snake_direction;
extern SNAKE_BLOCK_t food;
extern volatile uint8_t food_blink;
extern volatile uint16_t score;
extern volatile uint16_t highscore;
extern volatile uint8_t highscore_flag;
extern volatile uint8_t snake_lobby;
extern volatile uint8_t snake_pause;
extern volatile uint8_t snake_end;

void SNAKE_Clear_All(void);
void SNAKE_Draw_Block(uint8_t x, uint8_t y);
void SNAKE_Delete_Block(uint8_t x, uint8_t y);
void SNAKE_Init(void);
void SNAKE_Set_Direction(SNAKE_DIRECTION_t new_direction);
void SNAKE_Read_Joystick(void);
void SNAKE_Move(void);
void SNAKE_Draw_Self(void);
void SNAKE_Draw_Wall(void);
uint8_t SNAKE_Eat_Wall(void);
uint8_t SNAKE_Eat_Self(void);
uint8_t SNAKE_Eat_Food(void);

void Food_Spawn(void);
void Food_Blink(void);
uint8_t Food_On_Snake_Wall_Check(SNAKE_BLOCK_t food_check);

void Score_Scan(void);
void Highscore_Scan(void);

#endif
