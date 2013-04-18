//
//  Block.cpp
//  filament
//
//  Created by Kat Graff on 4/13/13.
//  Copyright (c) 2013 Kat Graff. All rights reserved.
//

#include "Block.h"
#include "Collision.h"
#include "TextureManager.h"

using namespace sf;

Block::Block(Vector2f pos, Color c) : position(pos), color(c)
{
    Texture* tex = texManager.getResource("/CS 2804/filament/res/block.png");
    sprite.setTexture(*tex);
    std::cout<<"Block created.\n";
}

void Block::draw(RenderTarget& target, RenderStates state) const{
    target.draw(sprite);
}
void Block::setPosition(Vector2f pos){
    position=pos;
}
bool Block::isCollidingWith(ICollidable& other) const {
    if ((Collision::BoundingBoxTest(sprite, other.getSprite())&&(this->getColor())!=other.getColor())) return true;
    return false;
}
void Block::update(Level& level, Time delta){
    //TODO
}
Sprite& Block::getSprite(){
    return sprite;
}
