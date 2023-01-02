#include "lsb.h"

int16_t u2_to_bin(uint8_t num1, uint8_t num2) {
    int16_t result;
    uint8_t sign = (num2 >> 1) & 1;
    if (sign == 1) {
        num1 -= 1;
        num2 = ~num2;
        num1 = ~num1;
    }
    num2 &= 0b11;
    num1 &= 0b11111111;
    result = num2 * (1 << 8) + num1;
    if (sign == 1) {
	result = -result;
    }
    //printf("u2tobin: %d\n", result);
    return result;
}

float normalize(int16_t num, int16_t min, int16_t range) {
	    return ((float)(num - min) / range);
}

int16_t change_range(float num, int16_t min, int16_t max) {
	    return (max - min) * num + min;
}

int16_t joystick_to_lcd_x(uint8_t num1, uint8_t num2){
	return change_range(normalize(u2_to_bin(num1, num2), -511, 1023), 0, 320);
}

int16_t joystick_to_lcd_y(uint8_t num1, uint8_t num2){
	return change_range(normalize(u2_to_bin(num1, num2), -511, 1023), 0, 240);
}

void test(void){
	uint8_t max_num1 = 0b11111111;
	uint8_t max_num2 = 0b00000001;
	int16_t max_x = joystick_to_lcd_x(max_num1, max_num2);
	int16_t max_y = joystick_to_lcd_y(max_num1, max_num2);
	printf("--------- Max --------------\n");
	printf("num1: %u, num2: %u\n", max_num1, max_num2);
	printf("result: %d %d\n", max_x, max_y);

	uint8_t min_num1 = 0b00000001;
	uint8_t min_num2 = 0b00000010;
	int16_t min_x = joystick_to_lcd_x(min_num1, min_num2);
	int16_t min_y = joystick_to_lcd_y(min_num1, min_num2);
	printf("--------- Min --------------\n");
	printf("num1: %u, num2: %u\n", min_num1, min_num2);
	printf("result: %d %d\n", min_x, min_y);

	uint8_t zero_num1 = 0b00000000;
	uint8_t zero_num2 = 0b00000000;
	int16_t zero_x = joystick_to_lcd_x(zero_num1, zero_num2);
	int16_t zero_y = joystick_to_lcd_y(zero_num1, zero_num2);
	printf("--------- U2 - Zero --------------\n");
	printf("num1: %u, num2: %u\n", zero_num1, zero_num2);
	printf("result: %d %d\n", zero_x, zero_y);
}
