#include "SNAKE.h"

volatile uint8_t snake_tick_count = 0;
volatile uint8_t snake_tick = 0;
volatile uint8_t button_count = 0;
volatile uint8_t button_stable = 0;
volatile uint8_t button_pressed = 0;
volatile uint8_t button_start = 0;
volatile uint8_t button_pause = 0;
SNAKE_STATE_t snake_state;
SNAKE_BLOCK_t snake[snake_max_length];
uint16_t snake_length;
SNAKE_DIRECTION_t snake_direction = RIGHT;
SNAKE_BLOCK_t food;
volatile uint8_t food_blink = 0;
volatile uint16_t score = 0;
volatile uint16_t highscore = 0;
volatile uint8_t highscore_flag = 0;
volatile uint8_t snake_lobby = 0;
volatile uint8_t snake_pause = 0;
volatile uint8_t snake_end = 0;


//GAME TICK
void TIM3_IRQHandler(void){
	if (TIM3_SR & (1 << 0)){

		snake_tick_count++;
		if (snake_tick_count == 10){
			snake_tick_count = 0;
			snake_tick = 1;
		}

		if (button_pressed == 1){
			button_count++;
		}
		if (button_count >= 3){
			button_pressed = 0;
			button_count = 0;
			button_stable = 1;
		}
		TIM3_SR &= ~(1 << 0);
	}
}

void SNAKE_Clear_All(void){
	for (int dy = 0; dy < game_height; dy++){
		for (int dx = 0; dx < game_width; dx++){
			SNAKE_Delete_Block(dx, dy);
		}
	}
}

void SNAKE_Draw_Block(uint8_t x, uint8_t y){
	if ((x >= game_width) || (y >= game_height)) return;

	uint8_t block_x = x * block_size;
	uint8_t block_y = y * block_size;

	if (block_x + block_size > oled_x) return;
	if (block_y + block_size > oled_y) return;

	for (int dy = 0; dy < block_size; dy++){
		for (int dx = 0; dx < block_size; dx++){
			OLED_Set_Pixel(block_x + dx, block_y + dy, WHITE);
		}
	}
}
void SNAKE_Delete_Block(uint8_t x, uint8_t y){
	if ((x < game_width) && (y < game_height)){
		uint8_t block_x = x * block_size;
		uint8_t block_y = y * block_size;

		for (int dy = 0; dy < block_size; dy++){
			for (int dx = 0; dx < block_size; dx++){
				OLED_Set_Pixel(block_x + dx, block_y + dy, BLACK);
			}
		}
	}
}

void SNAKE_Init(void){
	snake_length = 3;

	snake[0] = (SNAKE_BLOCK_t){15, 8};
	snake[1] = (SNAKE_BLOCK_t){14, 8};
	snake[2] = (SNAKE_BLOCK_t){13, 8};

	snake_direction = RIGHT;

	for (uint16_t i = 0; i < snake_length; i++){
		SNAKE_Draw_Block(snake[i].x, snake[i].y);
	}
}

void SNAKE_Set_Direction(SNAKE_DIRECTION_t new_direction){
	if (
			((snake_direction == UP) && (new_direction == DOWN))    ||
			((snake_direction == DOWN) && (new_direction == UP))    ||
			((snake_direction == LEFT) && (new_direction == RIGHT)) ||
			((snake_direction == RIGHT) && (new_direction == LEFT))
		){
		return;
	}
	else {
		snake_direction = new_direction;
	}
}
void SNAKE_Read_Joystick(void){
	uint16_t x = ADC_Read_Pin(ADC1) * 3300 / 4095;
	uint16_t y = ADC_Read_Pin(ADC2) * 3300 / 4095;

	if (x < 800){
		SNAKE_Set_Direction(UP);
	}
	else if (x > 3000){
		SNAKE_Set_Direction(DOWN);
	}
	else if (y < 800){
		SNAKE_Set_Direction(RIGHT);
	}
	else if (y > 3000){
		SNAKE_Set_Direction(LEFT);
	}
}

void SNAKE_Move(void){
	for (int i = snake_length - 1; i > 0; i--){
		snake[i] = snake[i - 1];
	}
	switch (snake_direction){
	case UP:    if (snake[0].y > 0){
		snake[0].y--; break;
	}
	case DOWN:  if (snake[0].y < game_height - 1){
		snake[0].y++; break;
	}
	case LEFT:  if (snake[0].x > 0){
		snake[0].x--; break;
	}
	case RIGHT: if (snake[0].x < game_width - 1){
		snake[0].x++; break;
	}
	default: break;
	}
}
void SNAKE_Draw_Self(void){
	for (int i = 0; i < snake_length; i++){
		SNAKE_Draw_Block(snake[i].x, snake[i].y);
	}
}

void SNAKE_Draw_Wall(void){
	for (uint8_t dy = 0; dy < game_height; dy++){
		SNAKE_Draw_Block(0, 0 + dy);
		SNAKE_Draw_Block(game_width - 1, 0 + dy);
	}
	for (uint8_t dx = 0; dx < game_width; dx++){
		SNAKE_Draw_Block(0 + dx, 0);
		SNAKE_Draw_Block(0 + dx, game_height - 1);
	}
}

uint8_t SNAKE_Eat_Wall(void){
	if ((snake[0].x <=0) || (snake[0].x >= game_width - 1)){
		return EATEN;
	}
	else if ((snake[0].y <= 0) || (snake[0].y >= game_height - 1)){
		return EATEN;
	}
	else{
		return NONE;
	}
}

uint8_t SNAKE_Eat_Self(void){
	for (int i = snake_length - 1; i > 0; i--){
		if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y)){
			return EATEN;
		}
	}
	return NONE;
}

uint8_t SNAKE_Eat_Food(void){
	if ((snake[0].x == food.x) && (snake[0].y == food.y)){
		snake_length++;
		return EATEN;
	}
	else {
		return NONE;
	}
}
void Food_Spawn(void){
	do {
		uint16_t random = TIM_Get_Random(TIM2);
		uint16_t random_x = random & 0xFF;
		uint16_t random_y = (random >> 8);

		food.x = random_x % game_width;
		food.y = random_y % game_height;
	} while (Food_On_Snake_Wall_Check(food) == ON);
}
void Food_Blink(void){
	if (food_blink == 1){
		SNAKE_Draw_Block(food.x, food.y);
		food_blink = 0;
	}
	else {
		SNAKE_Delete_Block(food.x, food.y);
		food_blink = 1;
	}
}

uint8_t Food_On_Snake_Wall_Check(SNAKE_BLOCK_t food_check){
	for (uint16_t i = 0; i < snake_length; i++){
		if ((food_check.x == snake[i].x) && (food_check.y == snake[i].y)){
			return ON;
		}
	}
	if ((food_check.x == 0) || (food_check.x == game_width - 1)){
		return ON;
	}
	if ((food_check.y == 0) || (food_check.y == game_height - 1)){
		return ON;
	}
	return NONE;
}

void Score_Scan(void){
	uint8_t ones;
	uint8_t tens;
	uint8_t hundreds;
	uint8_t thousands;

	ones      = score % 10;
	tens      = (score / 10) % 10;
	hundreds  = (score / 100) % 10;
	thousands = score / 1000;

	FOUR_BIT_LED_Scan(thousands, hundreds, tens, ones);
}
void Highscore_Scan(void){
	uint8_t ones;
	uint8_t tens;
	uint8_t hundreds;
	uint8_t thousands;

	ones      = highscore % 10;
	tens      = (highscore / 10) % 10;
	hundreds  = (highscore / 100) % 10;
	thousands = highscore / 1000;

	FOUR_BIT_LED_Scan(thousands, hundreds, tens, ones);
}










vaefdva




