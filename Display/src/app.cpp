#include "app.hpp"

extern int button_pressed;

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

    sf::Vector2u cursor(h / 2, w / 2);
    float speed = 1. / 25;
    //float s = 0.;
    int div = 1;
    bool clock_tick = false;
    int max_r = 141;
    
    auto f = [&div, &clock_tick]() {
        float speed = 1. / 25;
        //bool clock_tick = false;
        int time = 1. / (speed);
        //int div = 1;

        if (!sf::Joystick::isConnected(0)) {
            std::cout << "Error: Joystick not connected" << std::endl;
            return 0;
        }

        while (1) {
            Sleep(time/div);
            clock_tick = !clock_tick;
            //Sleep(/const);
        }
        //std::cout << "Exits" << std::endl;
    };
    std::thread counter(f);
    
        while (this->isOpen())
        {
            sf::Event event;
            while (this->pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    //std::terminate();
                    counter.detach();
                    this->close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Left) {
                        cursor.x--;
                    }
                    else if (event.key.code == sf::Keyboard::Right) {
                        cursor.x++;
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        cursor.y--;
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        cursor.y++;
                    }
                    if (event.key.code == sf::Keyboard::P) {
                        button_pressed++;
                    }
                    if (event.key.code == sf::Keyboard::L) {
                        button_pressed = 0;
                    }
                }
            }

            /*
            if (joystick_connected) {
                s = fabs(event.joystickMove.position) < 2 ? 0. : event.joystickMove.position;

                if (clock_tick) {
                    int sign = s / fabs(event.joystickMove.position);
                    cursor.y += event.joystickMove.axis * sign;
                    cursor.x += (1 - event.joystickMove.axis) * sign;
                }
                else {
                    speed = fabs(s) / 1000;
                    //std::cout << "speed:" << speed << std::endl;
                }
                std::cout << clock_tick << std::endl;

            }

            cursor.x = cursor.x >= 320 ? 319 : cursor.x;
            cursor.y = cursor.y >= 240 ? 239 : cursor.y;

            cursor.x = cursor.x <= 0 ? 0 : cursor.x;
            cursor.y = cursor.y <= 0 ? 0 : cursor.y;
            */

            if (clock_tick) {
                float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                float xPosition = fabs(x) < 2 ? 0. : x / fabs(x);
                float yPosition = fabs(y) < 2 ? 0. : y / fabs(y);
                int r = (int)sqrt(x * x + y * y);
                if (r > 3 * max_r / 4) {
                    div = 4;
                }
                else if (r > max_r / 2) {
                    div = 3;
                }
                else if (r > 1 * max_r / 4) {
                    div = 2;
                }
                else {
                    div = 1;
                }

                cursor.x += xPosition;
                cursor.y += yPosition;

                cursor.x = cursor.x >= 280 ? 279 : cursor.x;
                cursor.y = cursor.y >= 240 ? 239 : cursor.y;

                cursor.x = cursor.x <= 0 ? 0 : cursor.x;
                cursor.y = cursor.y <= 0 ? 0 : cursor.y;

            }

            canvas[cursor.x * w + cursor.y] = sf::Vertex(sf::Vector2f(cursor.x, cursor.y), sf::Color::White);
    
        this->clear();
        fun();
        std::size_t size = h * w;
        buffer.draw(canvas, size, sf::PrimitiveType::Points);
        buffer.display();
        this->draw(bufferSprite);

        this->display();
       }
}
