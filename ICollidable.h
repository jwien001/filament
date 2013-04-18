#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include <SFML/Graphics.hpp>

//Object that can collide with other things.
class ICollidable
{
    public:
        virtual ~ICollidable() {}

        virtual int getCollisionType() const = 0;
        virtual sf::FloatRect getCollisionBox() const = 0;
        virtual sf::Color getColor() const = 0;

        bool isCollidingWith(ICollidable& other) const {
            return getColor() != other.getColor() &&
                getCollisionBox().intersects(other.getCollisionBox());
        };
};

#endif // ICOLLIDABLE_H
