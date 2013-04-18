#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "ICollidable.h"
#include "ILevelObject.h"
#include "Collision.h"
#include "Level.h"

class Player : public ILevelObject, public ICollidable
{
    sf::Sprite sprite;
    sf::Color color;

    public:
        Player();

        sf::Vector2f getPosition() const {
            return sprite.getPosition();
        }

        void setPosition(sf::Vector2f pos) {
            sprite.setPosition(pos);
        }

        sf::Sprite& getSprite() {
            return sprite;
        }

        sf::Color getColor() const {
            return color;
        }

        bool isCollidingWith(ICollidable& other) const {
            return color != other.getColor() &&
                Collision::BoundingBoxTest(sprite, other.getSprite());
        }

        void update(Level& level, sf::Time delta);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // PLAYER_H
