#include "Projectile.h"
#include <iostream>

using namespace std;
using namespace sf;

const sf::Mouse::Button Projectile::BUTTON = Mouse::Left;

Projectile::Projectile(Player* player, const Vector2f& dir) : rect(Vector2f(8, 8)), direction(dir), oldPosition(), phasing(false), oldPhasing(false)
{
    setPosition(player->getCenter() + Vector2f(6, -17));
    oldPosition = getPosition();
    rect.setFillColor(player->getColor());
}

void Projectile::update(Level& level, Time delta) {
    oldPosition = getPosition();
    setPosition(oldPosition + (direction * 14.0f));

    oldPhasing = phasing;
    phasing = false;
}
