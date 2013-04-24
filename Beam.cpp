#include "Beam.h"
#include <iostream>

using namespace std;
using namespace sf;

const sf::Mouse::Button Beam::BUTTON = Mouse::Right;

Beam::Beam(Player* player) : rect()
{
    rect.setSize(Vector2f(5, 1));
    rect.setPosition(player->getCenter() + Vector2f(6, -17));
    rect.setOutlineColor(player->getColor());
    rect.setOutlineThickness(1);
}

void Beam::update(Level& level, Time delta) {
    Vector2f dx(32, 0);

    if (!Mouse::isButtonPressed(BUTTON))
        dx *= (float)-1.5;

    rect.setSize(rect.getSize() + dx);
}
