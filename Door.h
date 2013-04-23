#ifndef DOOR_H
#define DOOR_H

#include "Entity.h"

class Door : public Entity
{
    char id;
    bool activated;

    public:
        Door(sf::Vector2f pos, char c);

    void update(Level& level, sf::Time delta) override;

    void setActivated(bool a) {
        activated = a;
    }
};

#endif // DOOR_H
