#include "Door.h"
#include "TextureManager.h"

using namespace sf;

Door::Door(Vector2f pos, char c) : Entity(), id(c), activated(false)
{
    Texture* tex = texManager.getResource("res/img/door.png");
    sprite.setTexture(*tex);
    sprite.setPosition(pos);
}

void Door::update(Level& level, sf::Time delta) {
    if (activated)
        level.setDestination(id);
}
