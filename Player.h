#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
    public:
        const static int COLLISION_TYPE = 1;

        Player();

        int getCollisionType() const override {
            return COLLISION_TYPE;
        }

        void update(Level& level, sf::Time delta) override;
};

#endif // PLAYER_H
