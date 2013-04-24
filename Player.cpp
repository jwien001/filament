#include "Player.h"
#include "Beam.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define PI	 3.14159265358979323846

using namespace sf;

const float Player::SPEED = 4;
const float Player::JUMP = 12;
const float Player::GRAVITY = 0.6;

std::vector<sf::Color> Player::colorList = {Color::Black, Color::Red};
std::unordered_map<Color, std::string, ColorHash> Player::texMap = {
    {Color::Black, "/CS 2804/filament/res/img/black_dude.png"},
    {Color::Red, "/CS 2804/filament/res/img/red_dude.png"}
};

Player::Player() : Entity(), oldPosition(), colorIndex(-1), airborne(true), phasing(false), beam()
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

    int dt = delta.asMilliseconds();
    float newX = pos.x + (pos.x - oldPosition.x);
    float newY = pos.y + (pos.y - oldPosition.y) + (GRAVITY);

    setOldPosition(pos);
    setPosition(Vector2f(newX, newY));

    if (beam) {
        if (beam->getSize().x <= 0) {
            level.removeLevelObject(beam);
            level.removeCollidable(beam);
            beam.reset();
        }
        else
            beam->setPosition(getCenter() + Vector2f(6, -17));
    }

    airborne = true;
    phasing = false;
}

void Player::handleEvent(Event& event, Level& level) {
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::W && !airborne)
            oldPosition.y += JUMP;
        else if (event.key.code == Keyboard::Space && !phasing) {
            nextColor();

            if (beam) {
                level.removeLevelObject(beam);
                level.removeCollidable(beam);
                beam.reset();
            }
        }
    } else if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Beam::BUTTON) {
            if (!beam) {
                Beam* b = new Beam(this);
                Vector2f diff = Vector2f(event.mouseButton.x, event.mouseButton.y) - b->getPosition();
                b->setRotation(atan2(diff.y, diff.x) * 180 / PI);
                beam.reset(b);
                level.addLevelObject(beam);
                level.addCollidable(beam);
            }
        }
    } else if (event.type == Event::MouseMoved) {
        if (beam) {
            Vector2f diff = Vector2f(event.mouseMove.x, event.mouseMove.y) - beam->getPosition();
            beam->setRotation(atan2(diff.y, diff.x) * 180 / PI);
        }
    }
}
