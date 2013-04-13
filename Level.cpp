#include "Level.h"
#include "Player.h"

Level::Level() {
    std::shared_ptr<ILevelObject> plyr{new Player()};
    objects.push_back(plyr);
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
