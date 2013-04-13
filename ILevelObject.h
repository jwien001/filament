#ifndef ILEVELOBJECT_H
#define ILEVELOBJECT_H

#include "Level.h" 
using namespace sf;

//Object that exists within an object.
class ILevelObject : public Drawable
{
    public:
        virtual ~ILevelObject() {}
        virtual Vector2f getPosition() = 0;
        virtual void setPosition(Vector2f pos) = 0;
        virtual void update(Level& level, Time delta) = 0;
};

#endif // ILEVELOBJECT_H
