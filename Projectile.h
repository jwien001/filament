#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Player.h"

class Projectile : public ILevelObject, public ICollidable
{
    sf::RectangleShape rect;
    sf::Vector2f direction;
    sf::Vector2f oldPosition;
    bool phasing, oldPhasing;

    public:
        static const sf::Mouse::Button BUTTON;

        Projectile(Player* player, const sf::Vector2f& dir);

        void update(Level& level, sf::Time delta) override;

        const sf::Vector2f& getPosition() const override {
            return rect.getPosition();
        }

        void setPosition(const sf::Vector2f& pos) override {
            rect.setPosition(pos);
        }

        const sf::Vector2f& getOldPosition() const {
            return oldPosition;
        }

        sf::FloatRect getCollisionBox() const override {
            return rect.getGlobalBounds();
        }

        const sf::Color& getColor() const override {
            return rect.getFillColor();
        }

        bool isPhasing() const {
            return phasing;
        }

        bool wasPhasing() const {
            return oldPhasing;
        }

        bool isCollidingWith(ICollidable& other) override {
            if (!destroyed && getCollisionBox().intersects(other.getCollisionBox())) {
                if (getColor() != other.getColor())
                    return true;

                phasing = true;
            }
            return false;
        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(rect);
        };
};

#endif // PROJECTILE_H
