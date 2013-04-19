#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
    public:
        Player();

        void update(Level& level, sf::Time delta) override;
};

#endif // PLAYER_H
