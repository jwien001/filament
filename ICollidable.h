#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include <SFML/Graphics.hpp>

//Object that can collide with other things.
class ICollidable
{
    protected:
        bool destroyed;

    public:
        ICollidable() : destroyed(false) {}
        virtual ~ICollidable() {}

        virtual sf::FloatRect getCollisionBox() const = 0;
        virtual const sf::Color& getColor() const = 0;

        void setDestroyed(bool d) {
            destroyed = d;
        }

        virtual bool isCollidingWith(ICollidable& other) {
            return !destroyed &&
                getColor() != other.getColor() &&
                getCollisionBox().intersects(other.getCollisionBox());
        };
};

#endif // ICOLLIDABLE_H
