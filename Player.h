#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Entity.h"

class Player : public Entity
{
    /* These constants control the Player's movement */
    //SPEED is the horizontall move speed
    static const float SPEED;
    //JUMP controls the initial jump speed
    static const float JUMP;
    //GRAVITY determines how fast the Player falls
    static const float GRAVITY;

    sf::Vector2f oldPosition;
    bool airborne;
    bool jumping;

    public:
        Player();

        void update(Level& level, sf::Time delta) override;

        /**
         * Returns whether the Player is in the air or not.
         * This value is only valid from adfter all collisions have been processed
         * until the end of the Player's subsequent update cycle.
         */
        bool isAirborne() const {
            return airborne;
        }

        void setAirborne(bool a) {
            airborne = a;
        }

        const sf::Vector2f& getOldPosition() const {
            return oldPosition;
        }

        void setOldPosition(const sf::Vector2f& oldPos) {
            oldPosition = oldPos;
        }

        const sf::Vector2f& getCenter() const {
            sf::FloatRect box = sprite.getGlobalBounds();
            return sf::Vector2f(box.left + box.width/2, box.top + box.height/2);
        }
};

#endif // PLAYER_H
