#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

//Object that can collide with other things.
class ICollidable{
    public:
        virtual ~ICollidable() {}
        virtual Sprite& getSprite() = 0;
        virtual Color getColor() = 0;
        virtual bool isCollidingWith(ICollidable& other) = 0;
};

#endif // ICOLLIDABLE_H
