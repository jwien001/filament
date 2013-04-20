#ifndef ILEVELOBJECT_H
#define ILEVELOBJECT_H

#include "Level.h"

class Level;

//Object that exists within an object.
class ILevelObject : public sf::Drawable
{
    public:
        virtual ~ILevelObject() {}
        virtual const sf::Vector2f& getPosition() const = 0;
        virtual void setPosition(const sf::Vector2f& pos) = 0;
        virtual void update(Level& level, sf::Time delta) = 0;
};

#endif // ILEVELOBJECT_H
