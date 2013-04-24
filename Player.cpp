#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const float Player::SPEED = 4;
const float Player::JUMP = 12;
const float Player::GRAVITY = 0.035;

std::vector<sf::Color> Player::colorList = {Color::Black, Color::Red};
std::unordered_map<Color, std::string, ColorHash> Player::texMap = {
    {Color::Black, "/CS 2804/filament/res/img/black_dude.png"},
    {Color::Red, "/CS 2804/filament/res/img/red_dude.png"}
};

Player::Player() : Entity(), oldPosition(), colorIndex(-1), phasing(false), airborne(true), jumping(false)
{
    nextColor();
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
    if (Keyboard::isKeyPressed(Keyboard::Space) && !phasing)
        nextColor();

    int dt = delta.asMilliseconds();
    float newX = pos.x + (pos.x - oldPosition.x);
    float newY = pos.y + (pos.y - oldPosition.y) + (GRAVITY * dt);

    setOldPosition(pos);
    setPosition(Vector2f(newX, newY));

    airborne = true;
    phasing = false;
}
