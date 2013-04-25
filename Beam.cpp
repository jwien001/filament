#include "Beam.h"
#include <iostream>
#include <limits>

using namespace std;
using namespace sf;

const sf::Mouse::Button Beam::BUTTON = Mouse::Right;

Beam::Beam(Player* player) : rect(), numBlocks(0), traceNum(numeric_limits<int>::max())
{
    rect.setSize(Vector2f(5, 1));
    rect.setPosition(player->getCenter() + Vector2f(6, -17));
    rect.setOutlineColor(player->getColor());
    rect.setOutlineThickness(1);
}

void Beam::update(Level& level, Time delta) {
    if (Mouse::isButtonPressed(BUTTON))
        move(30);
    else
        move(30 * -1.5);

    traceNum = numeric_limits<int>::max();
}

void Beam::move(float count) {
    rect.setSize(rect.getSize() + Vector2f(count, 0));
}

int Beam::trace(ICollidable& other) {
    //Ray casting!
    sf::FloatRect mini(getPosition().x, getPosition().y, 1, 1);
    for (int i=0; i<rect.getSize().x; ++i) {
        if (mini.intersects(other.getCollisionBox()))
            return i;
        else {
            mini.left += cos(rect.getRotation() / 57.3);
            mini.top += sin(rect.getRotation() / 57.3);
        }
    }
    return -1;
}
