#ifndef COLLISIONHANDLERS_H
#define COLLISIONHANDLERS_H

#include "ICollidable.h"

typedef void (*CollisionHandler)(ICollidable&, ICollidable&);

class CollisionHandlers
{
    public:
        static void PlayerBlockHandler(ICollidable& a, ICollidable& b);
};

#endif // COLLISIONHANDLERS_H
