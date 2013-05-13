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
    Texture* tex;
    if (c == Color(127, 127, 127))
        tex = texManager.getResource("res/img/gray_block.png");
    else if (c == Color::Black)
        tex = texManager.getResource("res/img/black_block.png");
    else if (c == Color::Red)
        tex = texManager.getResource("res/img/red_block.png");
    sprite.setTexture(*tex);
    sprite.setPosition(pos);
}
