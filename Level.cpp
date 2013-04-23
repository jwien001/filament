#include <iostream>
#include <fstream>
#include "Level.h"
#include "Player.h"
#include "Block.h"

using namespace std;
using namespace sf;

const int Level::BLOCK_SIZE = 32;

Level::Level(string levelFile) : objects(), colManager(), levelSize() {
    ifstream file("/CS 2804/filament/res/map/" + levelFile);

    if (file.is_open()) {
        string line;
        getline(file, line);

        int y = 0, x;
        while (!file.eof()) {
            x = 0;
            for (char& c : line) {
                createObject(c, Vector2f(x, y));
                ++x;
            }

            line.clear();
            getline(file, line);
            ++y;
        }
        levelSize = Vector2f(x, y) * (float)BLOCK_SIZE;

        colManager.addHandler<Player, Block>(&CollisionHandlers::PlayerBlockHandler);
    }
}

void Level::createObject(char c, Vector2f pos) {
    pos *= (float)BLOCK_SIZE;

    shared_ptr<ILevelObject> lvlObj;
    shared_ptr<ICollidable> coll;
    shared_ptr<Entity> ent;

    switch (c) {
        case '0':
            ent = shared_ptr<Block>(new Block(pos));
            break;
        case '1':
            ent = shared_ptr<Block>(new Block(pos, Color::Black));
            break;
        case '2':
            ent = shared_ptr<Block>(new Block(pos, Color::Red));
            break;
        case '.':
            break;
        default:
            cout << "Invalid character in level file: " << c << endl;
    }

    if (lvlObj){}
    else if (coll){}
    else if (ent)
        addEntity(ent);
}

void Level::addEntity(shared_ptr<Entity> ent) {
    objects.push_back(ent);
    colManager.addCollidable(ent);
}

void Level::update(Time delta) {
    for (shared_ptr<ILevelObject> obj : objects) {
        obj->update(*this, delta);
    }

    colManager.processCollisions();
}

void Level::draw(RenderTarget& target, RenderStates states) const {
    for (shared_ptr<ILevelObject> obj : objects) {
        target.draw(*obj);
    }
}
