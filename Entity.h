#ifndef ENTITY_H
#define ENTITY_H

#include "ILevelObject.h"
#include "ICollidable.h"

class Entity : public ILevelObject, public ICollidable
{
    protected:
        sf::Sprite sprite;
        sf::Color color;

    public:
        Entity() : sprite(), color(127, 127, 127) {}
        Entity(sf::Color c) : sprite(), color(c) {}

        const sf::Vector2f& getPosition() const override {
            return sprite.getPosition();
        }

        void setPosition(const sf::Vector2f& pos) override {
            sprite.setPosition(pos);
        }

        sf::FloatRect getCollisionBox() const override {
            return sprite.getGlobalBounds();
        }

        const sf::Color& getColor() const override {
            return color;
        }

        void update(Level& level, sf::Time delta) override {
            //Do nothing
        };

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(sprite);
        };
};

#endif // ENTITY_H
