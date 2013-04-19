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
    Block(sf::Vector2f pos, sf::Color c);
};

#endif /* defined(__filament__Block__) */
