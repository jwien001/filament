#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include <SFML/Graphics.hpp>

//Object that can collide with other things.
class ICollidable
{
    public:
        virtual ~ICollidable() {}
        virtual sf::Sprite& getSprite() = 0;
        virtual sf::Color getColor() const = 0;
        virtual bool isCollidingWith(ICollidable& other) const = 0;
};

#endif // ICOLLIDABLE_H
