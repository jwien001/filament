#ifndef COLLISIONHANDLERS_H
#define COLLISIONHANDLERS_H

#include "ICollidable.h"

typedef void (*CollisionHandler)(ICollidable&, ICollidable&);

class CollisionHandlers
{
    public:
        static void PlayerBlockHandler(ICollidable& player, ICollidable& block);
};

#endif // COLLISIONHANDLERS_H
