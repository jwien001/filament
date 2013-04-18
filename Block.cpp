//
//  Block.cpp
//  filament
//
//  Created by Kat Graff on 4/13/13.
//  Copyright (c) 2013 Kat Graff. All rights reserved.
//

#include <iostream>
#include "Block.h"
#include "TextureManager.h"

using namespace sf;

Block::Block(Vector2f pos, Color c) : Entity(c)
{
    Texture* tex = texManager.getResource("/CS 2804/filament/res/block.png");
    sprite.setTexture(*tex);
    sprite.setPosition(pos);
    std::cout<<"Block created.\n";
}
