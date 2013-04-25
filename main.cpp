#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <memory>
#include "Block.h"
#include "TextureManager.h"
#include "Player.h"
#include "Level.h"


using namespace std;

int main()
{
    const sf::Vector2f screenSize(800, 600);

    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Filament Demo");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::View view(sf::FloatRect(0, 0, screenSize.x, screenSize.y));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));

    sf::Font font;
    font.loadFromFile("/CS 2804/filament/res/visitor1.ttf");

    sf::Clock clock;

    //Create player and first level
    shared_ptr<Player> player{new Player};
    Level level('1', player, 's');

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time delta = clock.restart();
        static sf::Vector2f mouse;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == Event::MouseMoved) {
                mouse.x = event.mouseMove.x;
                mouse.y = event.mouseMove.y;
            } else {
                player->handleEvent(event, level);
            }
        }

        level.setMouse(mouse + view.getCenter() - (screenSize / (float)2));

        level.update(delta);

        //Handle level transition
        if (level.getDestination() != '\0') {
            level = Level(level.getDestination(), player, level.getId());
            continue;
        }

        Vector2f center = player->getCenter();
        Vector2f levelSize = level.getSize() * Level::BLOCK_SIZE;

        //Center view on player, but keep it inside the level bounds
        if (center.x > levelSize.x - screenSize.x / 2)
            center.x = levelSize.x - screenSize.x / 2;
        if (center.x < screenSize.x / 2)
            center.x = screenSize.x / 2;

        if (center.y > levelSize.y - screenSize.y / 2)
            center.y = levelSize.y - screenSize.y / 2;
        if (center.y < screenSize.y / 2)
            center.y = screenSize.y / 2;

        view.setCenter(center);

        window.setView(view);
        window.clear(sf::Color::White);

        //Use special OpenGL rendering mode to create the color inversion effect
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_EQUIV);

        window.draw(level);

        glDisable(GL_COLOR_LOGIC_OP);

        player->drawUI(window, font, view);

        window.display();
    }

    return 0;
}
