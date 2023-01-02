#pragma once

#include <SFML/Graphics.hpp>

#define DEBUG_PRINT(x) if(debug){ debug = debug>>1; x; }
#define DEBUG_INIT unsigned int debug = 1;

typedef  void (*fun_ptr)();


class App : public sf::RenderWindow {
private:
    unsigned int hight;
    unsigned int width;
    std::string title;
    unsigned int resizer;
    unsigned int pixel_size;
public:
    sf::Vertex* canvas;

public:
    App(unsigned int hight = 320, unsigned int width = 240, std::string title = "Display", unsigned int resizer = 4);
    ~App();
 
private:
    class Pixel : public sf::RectangleShape {
    public:
        Pixel(unsigned int size = 4, sf::Color color = sf::Color::White)
            : sf::RectangleShape(sf::Vector2f(size, size)) {
            this->setFillColor(color);
        }
        unsigned int getSize() {
            return (unsigned int)sf::RectangleShape::getSize().x;
        }
    };

    void printPixel(Pixel& pixel, sf::RenderWindow& window);
    void drawPlus(Pixel& center, sf::RenderWindow& window, int size) ;

public:
    sf::Vector2u getCanvasSize();
    void run_demo();
    void run(fun_ptr fun);
};
