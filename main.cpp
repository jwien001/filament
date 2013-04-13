#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "Block.h"
#include "TextureManager.h"
#include "Level.h"


using namespace std;

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "My First SFML Game");
    window.setFramerateLimit(60);

    sf::RectangleShape shape(sf::Vector2f(200, 100));
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(100, 100);

    sf::Texture* pTex = texManager.getResource("/CS 2804/filament/res/dude.png");

    sf::Sprite pSpr;
    pSpr.setTexture(*pTex);

    Block blxx0rs = Block(sf::Vector2f(500,500),sf::Color::Black);

    sf::Clock clock;

    Level level;

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time delta = clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        level.update(delta);

        window.clear(sf::Color(255, 255, 255, 0));
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_EQUIV);
        window.draw(pSpr);
        window.draw(blxx0rs.getSprite());
        window.draw(shape);
        window.draw(level);
        glDisable(GL_COLOR_LOGIC_OP);
        window.display();
    }

    return 0;
}
