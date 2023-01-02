#include "app.hpp"

typedef  void (*fun_ptr)();


App::App(unsigned int hight, unsigned int width, std::string title, unsigned int resizer)
: sf::RenderWindow(sf::VideoMode(hight*resizer, width*resizer), title){
    canvas = new sf::Vertex[hight * width];

    hight *= resizer;
    width *= resizer;


    this->pixel_size = resizer;
    this->hight = hight;
    this->width = width;
    this->title = title;
    this->resizer = resizer;
}

App::~App() {
    if(canvas) delete canvas;
}

void App::printPixel(Pixel& pixel, sf::RenderWindow& window) {
    window.draw(pixel);
}

sf::Vector2u App::getCanvasSize() {
    return sf::Vector2u(hight / resizer, width / resizer);
}

void App::drawPlus(Pixel& center, sf::RenderWindow& window, int size) {
    unsigned int x = center.getPosition().x;
    unsigned int y = center.getPosition().y;
    int pixel_size = center.getSize();
    //DEBUG_PRINT(printf("%u %u %u\n", x, y, pixel_size));

    for (int i = 0; i < (2 * size + 1); i++) {
        Pixel cursor = center;
        cursor.move((-size + i) * pixel_size, 0);
        printPixel(cursor, window);
    }
    for (int i = 0; i < (2 * size + 1); i++) {
        Pixel cursor = center;
        cursor.move(0, (-size + i) * pixel_size);
        printPixel(cursor, window);
    }
}

void App::run_demo() {
    sf::Color pixel_color = sf::Color::White;
    Pixel cursor(pixel_size, pixel_color);
    Pixel p2(pixel_size, sf::Color::Red);
    cursor.setPosition(hight / 2, width / 2);
    p2.setPosition(hight / 2, width / 2);

    while (this->isOpen())
    {
        sf::Event event;
        while (this->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->close();
        }

        this->clear();
        //window.draw(cursor);
        drawPlus(cursor, *this, 2);
        printPixel(p2, *this);
        this->display();
    }
}
void App::run(fun_ptr fun) {
    unsigned int h = getCanvasSize().x;
    unsigned int w = getCanvasSize().y;
    
    sf::View view(sf::Vector2f(h / 2, w / 2), sf::Vector2f(h, w));
    this->setView(view);
    sf::RenderTexture buffer;
    buffer.create(h, w);
    sf::Sprite bufferSprite(buffer.getTexture());


    while (this->isOpen())
    {
        sf::Event event;
        while (this->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->close();
        }
        this->clear();
        fun();
        std::size_t size = h * w;
        buffer.draw(canvas, size, sf::PrimitiveType::Points);
        buffer.display();
        this->draw(bufferSprite);

        this->display();
    }
}
