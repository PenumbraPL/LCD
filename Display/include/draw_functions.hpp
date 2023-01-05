#pragma once

#include <SFML/Graphics.hpp>
#include "App.hpp"

extern "C" {
#include "asciiLib.h"
}


sf::Color convert_color(uint16_t color);
void printPixel(uint16_t x, uint16_t y, uint16_t color);
void fillBackground(uint16_t color);
void drawPlus(uint16_t x, uint16_t y, uint8_t size, uint16_t color);
void BresenhamLine(const int x1, const int y1, const int x2, const int y2, uint16_t color);
void drawcircle(int x0, int y0, int radius, uint16_t color);
void printString(unsigned short x, unsigned short y, const char* stringToPrint, uint16_t bgColor);
void fillRectangle(uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd, uint16_t color);
void printImage(unsigned short x, unsigned short y, unsigned int img, uint16_t color, uint16_t bgColor);

