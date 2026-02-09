#ifndef __BITMAP_H
#define __BITMAP_H
#include <stdint.h>

#define bitmap_x    128
#define bitmap_y    64

extern const uint8_t SNAKE_LOBBY_1[bitmap_x * (bitmap_y / 8)];
extern const uint8_t SNAKE_LOBBY_2[bitmap_x * (bitmap_y / 8)];
extern const uint8_t SNAKE_PAUSE_1[bitmap_x * (bitmap_y / 8)];
extern const uint8_t SNAKE_PAUSE_2[bitmap_x * (bitmap_y / 8)];
extern const uint8_t SNAKE_END_1[bitmap_x * (bitmap_y / 8)];
extern const uint8_t SNAKE_END_2[bitmap_x * (bitmap_y / 8)];
extern const uint8_t SNAKE_END_HIGHSCORE[bitmap_x * (bitmap_y / 8)];

void OLED_Convert_CF1_To_Buffer(
    const uint8_t *src,
    uint8_t *dst,
    uint16_t width,
    uint16_t height
);

#endif
