#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

using namespace sf;

const float Player::SPEED = 3;
const float Player::JUMP = 9;
const float Player::GRAVITY = 0.03;

Player::Player() : Entity(Color::Red), oldPosition(), airborne(true), jumping(false)
{
    Texture* tex = texManager.getResource("/CS 2804/filament/res/img/dude.png");
    sprite.setTexture(*tex);
    sprite.setPosition(40, 40);
    oldPosition = Vector2f(40, 40);
}

void Player::update(Level& level, Time delta) {
    Vector2f pos = getPosition();
    oldPosition.x = pos.x;

    if (Keyboard::isKeyPressed(Keyboard::A))
        oldPosition.x += SPEED;
    if (Keyboard::isKeyPressed(Keyboard::D))
        oldPosition.x -= SPEED;
    if (Keyboard::isKeyPressed(Keyboard::W) && !airborne && !jumping) {
        oldPosition.y += JUMP;
        jumping = true;
    }
    if (!Keyboard::isKeyPressed(Keyboard::W))
        jumping = false;

    int dt = delta.asMilliseconds();
    float newX = pos.x + (pos.x - oldPosition.x);
    float newY = pos.y + (pos.y - oldPosition.y) + (GRAVITY * dt);

    setOldPosition(pos);
    setPosition(Vector2f(newX, newY));

    airborne = true;
}
