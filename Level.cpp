#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "Level.h"
#include "Player.h"
#include "Block.h"
#include "Door.h"

using namespace std;
using namespace sf;

const float Level::BLOCK_SIZE = 32;

Level::Level(string levelFile) : objects(), colManager(), levelSize(),
        player(), transition() {
    ifstream file("/CS 2804/filament/res/map/" + levelFile);

    if (file.is_open()) {
        vector<string> lines;

        copy(istream_iterator<string>(file), istream_iterator<string>(), back_inserter(lines));

        int width = lines[0].length();
        int height = lines.size();
        levelSize = Vector2f(width, height);

        char mapData[width][height];

        for (int y=0; y<height; ++y)
            for (int x=0; x<width; ++x)
                mapData[x][y] = lines[y][x];

        for (int y=0; y<height; ++y) {
            for (int x=0; x<width; ++x) {
                if (mapData[x][y] == 'd') {
                    addEntity(shared_ptr<Door>{new Door(Vector2f(x, y) * BLOCK_SIZE, mapData[x][y+1])});
                    mapData[x][y+1] = '.';
                }
                else
                    createObject(mapData[x][y], Vector2f(x, y));
            }
        }

        colManager.addHandler<Player, Block>(&CollisionHandlers::PlayerBlockHandler);
        colManager.addHandler<Player, Door>(&CollisionHandlers::PlayerDoorHandler);
    }
}

void Level::createObject(char c, Vector2f pos) {
    pos *= BLOCK_SIZE;

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
        default:;
            cout << "Invalid character in level file: " << c << endl;
    }

    if (lvlObj){}
    else if (coll){}
    else if (ent)
        addEntity(ent);
}

void Level::setPlayer(shared_ptr<Player> plyr) {
    if (player)
        colManager.removeCollidable(plyr);
    player = plyr;
    colManager.addCollidable(plyr);
}

void Level::addEntity(shared_ptr<Entity> ent) {
    objects.push_back(ent);
    colManager.addCollidable(ent);
}

void Level::update(Time delta) {
    for (shared_ptr<ILevelObject> obj : objects) {
        obj->update(*this, delta);
    }
    player->update(*this, delta);

    colManager.processCollisions();
}

void Level::draw(RenderTarget& target, RenderStates states) const {
    for (shared_ptr<ILevelObject> obj : objects) {
        target.draw(*obj);
    }
    target.draw(*player);
}
