#include "Level.h"
#include "Player.h"
#include "Block.h"

Level::Level() {
    std::shared_ptr<ILevelObject> plyr{new Player()};
    std::shared_ptr<ILevelObject> block{new Block(Vector2f(500,500), Color::Black)};

    objects.push_back(plyr);
    objects.push_back(block);
}

void Level::update(Time delta) {
    for (std::shared_ptr<ILevelObject> obj : objects) {
        obj->update(*this, delta);
    }
}

void Level::draw(RenderTarget& target, RenderStates states) const {
    for (std::shared_ptr<ILevelObject> obj : objects) {
        target.draw(*obj);
    }
}
