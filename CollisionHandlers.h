#ifndef COLLISIONHANDLERS_H
#define COLLISIONHANDLERS_H

#include <memory>
#include "ICollidable.h"

class Level;

typedef void (*CollisionHandler)(std::shared_ptr<ICollidable>, std::shared_ptr<ICollidable>, Level&);

class CollisionHandlers
{
    public:
        static void PlayerBlockHandler(std::shared_ptr<ICollidable> player, std::shared_ptr<ICollidable> block, Level& level);
        static void PlayerDoorHandler(std::shared_ptr<ICollidable> player, std::shared_ptr<ICollidable> door, Level& level);
        static void BeamBlockHandler(std::shared_ptr<ICollidable> beam, std::shared_ptr<ICollidable> block, Level& level);
};

#endif // COLLISIONHANDLERS_H
