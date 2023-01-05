#include <SFML/Graphics.hpp>
#include "app.hpp"
#include "draw_functions.hpp"

extern "C" {
#include "asciiLib.h"
#include "lsb.h"
}

App app;
int button_pressed = 0;
/* ================================================================================== */


void test1() {
    uint16_t hight = app.getCanvasSize().x;
    uint16_t width = app.getCanvasSize().y;
    uint16_t size = 2;
    uint16_t color = 0xFFFF;

    drawPlus(hight / 2, width / 2, size, color);
}

void test2() {
    uint16_t hight = app.getCanvasSize().x;
    uint16_t width = app.getCanvasSize().y;
    uint16_t color = 0xFFFF;

    uint16_t x0 = hight / 2;
    uint16_t y0 = width / 2;
    uint16_t radius = 10;

    drawcircle(x0, y0, radius, color);
}

void test3() {
    int x1 = 5;
    int y1 = 5;
    int x2 = 105;
    int y2 = 105;
    uint16_t color = 0xFFFF;

    BresenhamLine(x1, y1, x2, y2, color);
}

void test4() {
    uint16_t color = 0xFFFF;
    uint16_t background = 0x001F;
    uint16_t div = 4;
    uint16_t div_length = app.getCanvasSize().y / (div+1);
    
    fillRectangle(280, 320, 0, div_length, background);
    BresenhamLine(280, 0, 280, 239, color);
    for (int i = 1; i <= div; i++) {
       BresenhamLine(280, i * div_length, 319, i * div_length, color);
    }
}

void test5() {
    uint16_t color = 0xFFFF;
    uint16_t x = app.getCanvasSize().x / 2;
    uint16_t y = app.getCanvasSize().y / 2;

    fillBackground(color);
    printString(x, y, "String", color);
}

void test6_bg(int position) {
    uint16_t color = 0x0000;
    uint16_t background = 0x001F;
    uint16_t c = color;
    uint16_t div = 4;
    uint16_t div_length = app.getCanvasSize().y / (div + 1);

    if (position != 0) {
        for (int i = 1; i <= div; i++) {
            if (position == i) c = background;
            else c = color;
            fillRectangle(290, 319, (i - 1) * div_length+1, i * div_length-1, c);
        }
    }
}

void test6() {
    uint16_t color = 0xFFFF;
    uint16_t background = 0x001F;
    uint16_t div = 4;
    uint16_t div_length = app.getCanvasSize().y / (div + 1);

    test4();
    test6_bg(button_pressed);

    for (int i = 1; i <= div; i++) {
        printImage(290, i*div_length+10, i-1, color, background);
    }
}

int main()
{
    //app.run_demo();
    
    //app.run(test1);
    //app.run(test2);
    //app.run(test3);
    //app.run(test4);
    //app.run(test5);
    app.run(test6);


    return 0;
}