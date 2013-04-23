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
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First SFML Game");
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));

    sf::Clock clock;

    shared_ptr<Player> player{new Player};
    Level level("level1.txt");
    level.addEntity(player);

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

        view.setCenter(sf::Vector2f(player->getCenter())); //Must invoke copy constuctor, otherwise center data is lost
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
