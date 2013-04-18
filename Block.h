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

class Block: public ICollidable, public ILevelObject
{
public:
    sf::Color getColor() const {return color;}
    sf::Vector2f getPosition() const {return position;}
    Block(sf::Vector2f pos, sf::Color c);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setPosition(sf::Vector2f pos);
    bool isCollidingWith(ICollidable& other) const;
    void update(Level& level, sf::Time delta);
    sf::Sprite& getSprite();
private:
    sf::Vector2f position;
    sf::Color color;
    sf::Sprite sprite;
};

#endif /* defined(__filament__Block__) */
