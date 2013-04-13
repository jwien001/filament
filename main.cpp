#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "TextureManager.h"

using namespace std;

int main()
{
    float x = 20;
    float y = 30;

    sf::RenderWindow window(sf::VideoMode(800, 600), "My First SFML Game");
    window.setFramerateLimit(60);

    sf::RectangleShape shape(sf::Vector2f(200, 100));
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(100, 100);

    sf::Texture* pTex = texManager.getResource("/CS 2804/filament/res/dude.png");

    sf::Sprite pSpr;
    pSpr.setTexture(*pTex);

    sf::Sprite pSpr2;
    pSpr2.setTexture(*pTex);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time delta = clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            x -= 0.2f * delta.asMilliseconds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            x += 0.2f * delta.asMilliseconds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            y -= 0.2f * delta.asMilliseconds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            y += 0.2f * delta.asMilliseconds();

        pSpr2.setPosition(x, y);

        cout<<x<<" "<<y<<endl;

        window.clear(sf::Color(255, 255, 255, 0));
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_EQUIV);
        window.draw(pSpr);
        window.draw(pSpr2);
        window.draw(shape);
        glDisable(GL_COLOR_LOGIC_OP);
        window.display();
    }

    return 0;
}
