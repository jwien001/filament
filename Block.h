//
//  Block.h
//  filament
//
//  Created by Kat Graff on 4/13/13.
//  Copyright (c) 2013 Kat Graff. All rights reserved.
//

#ifndef __filament__Block__
#define __filament__Block__

#include "Entity.h"

class Block : public Entity
{
public:
    const static int COLLISION_TYPE = 2;

    Block(sf::Vector2f pos, sf::Color c);

    int getCollisionType() const override {
        return COLLISION_TYPE;
    }
};

#endif /* defined(__filament__Block__) */
