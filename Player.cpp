#include <iostream>
#include <cmath>
#include "Player.h"
#include "Beam.h"
#include "Projectile.h"

using namespace sf;

const float Player::SPEED = 4;
const float Player::JUMP = 12;
const float Player::GRAVITY = 0.6;

std::vector<sf::Color> Player::colorList = {Color::Black, Color::Red};
std::unordered_map<Color, std::string, ColorHash> Player::texMap = {
    {Color::Black, "/CS 2804/filament/res/img/black_dude.png"},
    {Color::Red, "/CS 2804/filament/res/img/red_dude.png"}
};

Player::Player() : Entity(), inventory(), oldPosition(), colorIndex(-1), airborne(true), phasing(false), beam()
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
        inventory[colorList[colorIndex]] += beam->removeBlocks();
        if (beam->getSize().x <= 0) {
            level.removeLevelObject(beam);
            level.removeCollidable(beam);
            beam.reset();
        }
        else {
            beam->setPosition(getCenter() + Vector2f(6, -17));
            Vector2f diff = level.getMouse() - beam->getPosition();
            beam->setRotation(atan2(diff.y, diff.x) * 57.3);
        }
    }

    airborne = true;
    phasing = false;
}

void Player::drawUI(sf::RenderTarget& target, Font& font, View& view) {
    int boxWidth = 40;
    int boxBuffer = 16;
    int totalWidth = (boxWidth + boxBuffer) * colorList.size();
    float centerAlign = view.getCenter().x - (totalWidth / 2);
    float topAlign = view.getCenter().y - (view.getSize().y / 2) + boxBuffer;

    for (int i=0; i<colorList.size(); ++i) {
        RectangleShape rect(Vector2f(boxWidth, 32));
        rect.setFillColor(Color::White);
        rect.setOutlineColor(Color(127, 127, 127));
        rect.setOutlineThickness(2);
        rect.setPosition(centerAlign + (boxWidth + boxBuffer) * i, topAlign);

        std::stringstream ss;
        int count = inventory[colorList[i]];
        if (count < 10)
            ss << "0";
        ss << count;
        Text text(ss.str(), font, 30);
        text.setColor(colorList[i]);
        text.setPosition(centerAlign + (boxWidth + boxBuffer) * i + 4, topAlign - 8);

        target.draw(rect);
        target.draw(text);
    }
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
                Vector2f diff = level.getMouse() - b->getPosition();
                b->setRotation(atan2(diff.y, diff.x) * 57.3);
                beam.reset(b);
                level.addLevelObject(beam);
                level.addCollidable(beam);
            }
        } else if (event.mouseButton.button == Projectile::BUTTON) {
            if (inventory[colorList[colorIndex]] > 0 && !phasing) {
                Vector2f diff = level.getMouse() - (getCenter() + Vector2f(6, -17));
                float mag = sqrt(diff.x*diff.x + diff.y*diff.y);
                std::shared_ptr<Projectile> proj{new Projectile(this, diff / mag)};
                level.addLevelObject(proj);
                level.addCollidable(proj);
                --inventory[colorList[colorIndex]];
            }
        }
    }
}
