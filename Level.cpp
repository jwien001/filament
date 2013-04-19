#include <iostream>
#include "Level.h"
#include "Player.h"
#include "Block.h"

using namespace sf;

Level::Level() {
    std::shared_ptr<Player> plyr{new Player()};
    std::shared_ptr<Block> block{new Block(Vector2f(500,500), Color::Black)};

    objects.push_back(plyr);
    objects.push_back(block);

    colManager.addCollidable(plyr);
    colManager.addCollidable(block);
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
