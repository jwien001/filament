#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include <SFML/Graphics.hpp>

//Object that can collide with other things.
class ICollidable
{
    public:
        virtual ~ICollidable() {}

        virtual sf::FloatRect getCollisionBox() const = 0;
        virtual const sf::Color& getColor() const = 0;

        virtual bool isCollidingWith(ICollidable& other) {
            return getColor() != other.getColor() &&
                getCollisionBox().intersects(other.getCollisionBox());
        };
};

#endif // ICOLLIDABLE_H
