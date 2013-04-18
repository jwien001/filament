#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

using namespace sf;

Player::Player() : Entity(Color::Red)
{
    Texture* tex = texManager.getResource("/CS 2804/filament/res/dude.png");
    sprite.setTexture(*tex);
    sprite.setPosition(20, 30);
}

void Player::update(Level& level, Time delta) {
    Vector2f diff;
    if(Keyboard::isKeyPressed(Keyboard::A))
        diff.x = -0.2f * delta.asMilliseconds();
    if(Keyboard::isKeyPressed(Keyboard::D))
        diff.x = 0.2f * delta.asMilliseconds();
    if(Keyboard::isKeyPressed(Keyboard::W))
        diff.y = -0.2f * delta.asMilliseconds();
    if(Keyboard::isKeyPressed(Keyboard::S))
        diff.y = 0.2f * delta.asMilliseconds();

    sprite.move(diff);
}
