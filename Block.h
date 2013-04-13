//
//  Block.h
//  filament
//
//  Created by Kat Graff on 4/13/13.
//  Copyright (c) 2013 Kat Graff. All rights reserved.
//

#ifndef __filament__Block__
#define __filament__Block__

#include "ICollidable.h"
#include <iostream>
#include "ILevelObject.h"

class Block: public ICollidable, ILevelObject
{
public:
    Color getColor() const {return color;}
    Vector2f getPosition() const {return position;}
    Block(Vector2f pos, Color c);
    void draw(RenderTarget& target, RenderStates states) const;
    void setPosition(Vector2f pos);
    bool isCollidingWith(ICollidable& other) const;
    void update(Level& level, Time delta);
    Sprite& getSprite();
private:
    Vector2f position;
    Color color;
    Sprite sprite;
};

#endif /* defined(__filament__Block__) */
