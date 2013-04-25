#ifndef BEAM_H
#define BEAM_H

#include "Player.h"

class Beam : public ILevelObject, public ICollidable
{
    sf::RectangleShape rect;

    public:
        static const sf::Mouse::Button BUTTON;

        Beam(Player* player);

        void update(Level& level, sf::Time delta) override;
        void move(float count);

        const sf::Vector2f& getPosition() const override {
            return rect.getPosition();
        }

        void setPosition(const sf::Vector2f& pos) override {
            rect.setPosition(pos);
        }

        sf::FloatRect getCollisionBox() const override {
            return rect.getGlobalBounds();
        }

        const sf::Color& getColor() const override {
            return rect.getOutlineColor();
        }

        const sf::Vector2f& getSize() const {
            return rect.getSize();
        }

        void setRotation(float angle) {
            rect.setRotation(angle);
        }

        bool isCollidingWith(ICollidable& other) override {
            return getCollisionBox().intersects(other.getCollisionBox()) && trace(other) >=0;
        };

        int trace(ICollidable& other);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(rect);
        };
};

#endif // BEAM_H
