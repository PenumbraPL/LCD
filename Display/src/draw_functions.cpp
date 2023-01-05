#include "draw_functions.hpp"

extern App app;

sf::Color convert_color(uint16_t color) {
    sf::Color c;

    c.b = (color) & ((2 << 5) - 1);
    c.g = (color >> 5) & ((2 << 6) - 1);
    c.r = (color >> 11) & ((2 << 5) - 1);

    // Convert to 8-bit canal
    c.r *= 8;
    c.g *= 4;
    c.b *= 8;

    return c;
}

void printPixel(uint16_t x, uint16_t y, uint16_t color) {
    sf::Color c = convert_color(color);
    unsigned int width = app.getCanvasSize().y;
    app.canvas[x* width + y] = sf::Vertex(sf::Vector2f(x, y), c);
}

void fillBackground(uint16_t color) {
    unsigned int h = app.getCanvasSize().x;
    unsigned int w = app.getCanvasSize().y;
    unsigned int size = h * w;
    sf::Color c = convert_color(color);
    for (unsigned int i = 0; i < size; i++) {
        unsigned int x = i / w;
        unsigned int y = i % w;
        app.canvas[i] = sf::Vertex(sf::Vector2f(x, y), c);
    }
}

void drawPlus(uint16_t x, uint16_t y, uint8_t size, uint16_t color) {
    for (int i = 0; i < 2 * size + 1; i++) {
        printPixel(x - size + i, y, color);
    }
    for (int i = 0; i < 2 * size + 1; i++) {
        printPixel(x, y - size + i, color);
    }
}


void BresenhamLine(const int x1, const int y1, const int x2, const int y2, uint16_t color) {
    // zmienne pomocnicze
    int d, dx, dy, ai, bi, xi, yi;
    int x = x1, y = y1;
    
    // ustalenie kierunku rysowania
    if (x1 < x2){
        xi = 1;
        dx = x2 - x1;
    } else {
        xi = -1;
        dx = x1 - x2;
    }
    if (y1 < y2) {
        yi = 1;
        dy = y2 - y1;
    } else {
        yi = -1;
        dy = y1 - y2;
    }

    // pierwszy piksel
    printPixel(x, y, color);
    // os wiodaca OX
    if (dx > dy) {
        ai = (dy - dx) * 2;
        bi = dy * 2;
        d = bi - dx;
        // petla po kolejnych x
        while (x != x2) {
            // test wspólczynnika
            if (d >= 0) {
                x += xi;
                y += yi;
                d += ai;
            } else {
                d += bi;
                x += xi;
            }
            printPixel(x, y, color);
        }
    } else { // os wiodaca OY
        ai = (dx - dy) * 2;
        bi = dx * 2;
        d = bi - dy;
        // petla po kolejnych y
        while (y != y2) {
            // test wspólczynnika
            if (d >= 0) {
                x += xi;
                y += yi;
                d += ai;
            } else {
                d += bi;
                y += yi;
            }
            printPixel(x, y, color);
        }
    }
}

void drawcircle(int x0, int y0, int radius, uint16_t color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        printPixel(x0 + x, y0 + y, color);
        printPixel(x0 + y, y0 + x, color);
        printPixel(x0 - y, y0 + x, color);
        printPixel(x0 - x, y0 + y, color);
        printPixel(x0 - x, y0 - y, color);
        printPixel(x0 - y, y0 - x, color);
        printPixel(x0 + y, y0 - x, color);
        printPixel(x0 + x, y0 - y, color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void printString(unsigned short x, unsigned short y, const char* stringToPrint, uint16_t bgColor) {
    const unsigned char width = 8;
    const unsigned char height = 16;
    // ------------ 
    const unsigned int LCDBlack = 0x0000;
    // ------------ 
    int i = 0;
    unsigned char character = stringToPrint[i];
    unsigned char characterPixelsBuffer[height];
    int cursorX = x;
    while (character != '\0') {
        GetASCIICode(ASCII_8X16_MS_Gothic, characterPixelsBuffer, character);
        for (int k = 0; k < height; k++) {
            for (int j = 0; j < width; j++) {
                unsigned char mask = 1 << (width - j - 1);
                if ((characterPixelsBuffer[k] & mask) != 0) {
                    printPixel(x + i * width + j, y + k, LCDBlack);
                }
                else {
                    printPixel(x + i * width + j, y + k, bgColor);
                }
            }
        }
        character = stringToPrint[++i];
    }
}

void fillRectangle(uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd, uint16_t color) {
    for(int x=xStart; x<xEnd; x++){
        for (int y = yStart; y < yEnd; y++) {
            printPixel(x, y, color);
        }
    }
}

void printImage(unsigned short x, unsigned short y, unsigned int img, uint16_t color,uint16_t bgColor) {
    const unsigned char width = 16;
    const uint16_t height = 16;
    //uint16_t image[] = { 0x0000,0x0006,0x004,0x0806,0x1804,0x1E60,0x13F0,0x10B0,0x21B0,0x2130,0x6330,0x4230,0x6230,0x3E30,0x0430, 0x0030 };
        // { 0x4000,0x4022,0x6036,0x6014,0x201C,0x3208,0x3708,0x1580,0x3480,0x26C0,0x3240,0x3360,0x1130,0x1118,0x1F0C, 0x0006 };
        // { 0x0000,0x0018,0x0010,0x0010,0x0010,0x0018,0x0F00,0x30C0,0x2040,0x4020,0x4020,0x4020,0x2040,0x30C0,0x0F00, 0x0000 };
        // { 0xE000,0xE000,0xF810,0xF810,0xFC10,0x7C10,0x7C18,0x3E00,0x3E00,0x3F00,0x3F80,0x1F80,0x0F80,0x0FC0,0x07E0,0x07E0 };
    uint16_t image[height];
    GetImage(image, img);
    for (int k = 0; k < height; k++) {
        for (int j = 0; j < width; j++) {
            uint16_t mask = 1 << (width - j - 1);
            if ((image[k] & mask) != 0) {
                printPixel(x + j, y + k, color);
            }
            else {
                printPixel(x + j, y + k, bgColor);
            }
        }
    }
}