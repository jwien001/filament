#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "ICollidable.h"
#include "ILevelObject.h"
#include "Collision.h"
#include "Level.h"

using namespace sf;

class Player : public ILevelObject, public ICollidable
{
    Sprite sprite;
    Color color;

    public:
        Player();

        Vector2f getPosition() const {
            return sprite.getPosition();
        }

        void setPosition(Vector2f pos) {
            sprite.setPosition(pos);
        }

        Sprite& getSprite() {
            return sprite;
        }

        Color getColor() const {
            return color;
        }

        bool isCollidingWith(ICollidable& other) const {
            return color != other.getColor() &&
                Collision::BoundingBoxTest(sprite, other.getSprite());
        }

        void update(Level& level, Time delta);

        void draw(RenderTarget& target, RenderStates states) const;
};

#endif // PLAYER_H
