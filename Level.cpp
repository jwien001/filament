#include <iostream>
#include "Level.h"
#include "Player.h"
#include "Block.h"

using namespace sf;

Level::Level() {
    std::shared_ptr<Player> plyr{new Player()};
    std::shared_ptr<Block> block{new Block(Vector2f(20,200), Color::Black)};
    std::shared_ptr<Block> block2{new Block(Vector2f(20+192,200-64), Color::Black)};
    std::shared_ptr<Block> block3{new Block(Vector2f(20+128,200), Color::Black)};

    objects.push_back(plyr);
    objects.push_back(block);
    objects.push_back(block2);
    objects.push_back(block3);

    colManager.addCollidable(plyr);
    colManager.addCollidable(block);
    colManager.addCollidable(block2);
    colManager.addCollidable(block3);
    colManager.addHandler<Player, Block>(&CollisionHandlers::PlayerBlockHandler);
}

void Level::update(Time delta) {
    for (std::shared_ptr<ILevelObject> obj : objects) {
        obj->update(*this, delta);
    }

    colManager.processCollisions();
}

void Level::draw(RenderTarget& target, RenderStates states) const {
    for (std::shared_ptr<ILevelObject> obj : objects) {
        target.draw(*obj);
    }
}
