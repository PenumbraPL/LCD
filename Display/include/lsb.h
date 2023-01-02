#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

// num1 - Low, num2 = High
// return - binary number from u2
int16_t u2_to_bin(uint8_t num1, uint8_t num2);

// num - binary number, min - minimal value of number, range - number of possible values of number
// return number [0, 1]
float normalize(int16_t num, int16_t min, int16_t range);

// num - number [0, 1], min_x - minimal value of new number, max - maximal value of new number
// return number [min, max]
int16_t change_range(float num, int16_t min, int16_t max);

// values adjusted to LCD
int16_t joystick_to_lcd_x(uint8_t num1, uint8_t num2);
int16_t joystick_to_lcd_y(uint8_t num1, uint8_t num2);

void test(void);

#ifdef __cplusplus
}
#endif