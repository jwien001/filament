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

    sf::View view(sf::FloatRect(0, 0, screenSize.x, screenSize.y));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));

    sf::Clock clock;

    shared_ptr<Player> player{new Player};
    Level level("level1.txt");
    level.setPlayer(player);

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

        if (level.getTransition() != '\0') {
            stringstream ss;
            ss << "level" << level.getTransition() << ".txt";
            level = Level(ss.str());
            level.setPlayer(player);
            player->setPosition(sf::Vector2f(40, 40));
            player->setOldPosition(sf::Vector2f(40, 40));
            continue;
        }

        Vector2f center = player->getCenter();
        Vector2f levelSize = level.getSize() * Level::BLOCK_SIZE;

        if (center.x < screenSize.x / 2)
            center.x = screenSize.x / 2;
        else if (center.x > levelSize.x - screenSize.x / 2)
            center.x = levelSize.x - screenSize.x / 2;

        if (center.y < screenSize.y / 2)
            center.y = screenSize.y / 2;
        else if (center.y > levelSize.y - screenSize.y / 2)
            center.y = levelSize.y - screenSize.y / 2;

        view.setCenter(center);

        window.setView(view);
        window.clear(sf::Color::White);

        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_EQUIV);

        window.draw(level);

        glDisable(GL_COLOR_LOGIC_OP);
        window.display();
    }

    return 0;
}
