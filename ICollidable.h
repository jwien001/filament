#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

using namespace sf;

public class ICollidable
{
    public:
        virtual ~ICollidable() {}

        virtual Sprite& getSprite() = 0;
        virtual Color getColor() = 0;
        virtual bool isCollidingWith(ICollidable other) = 0;
};

#endif // ICOLLIDABLE_H