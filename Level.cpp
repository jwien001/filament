#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "Level.h"
#include "Player.h"
#include "Block.h"
#include "Door.h"
#include "Beam.h"
#include "Projectile.h"

using namespace std;
using namespace sf;

const float Level::BLOCK_SIZE = 32;

Level::Level(char level, shared_ptr<Player> plyr, char src) : id(level), objects(), colManager(),
        levelSize(), player(plyr), destination('\0'), mousePos() {
    stringstream ss;
    ss << "res/map/level" << id << ".txt";
    ifstream file(ss.str());

    if (file.is_open()) {
        vector<string> lines;

        //Read file line-by-line into string vector
        copy(istream_iterator<string>(file), istream_iterator<string>(), back_inserter(lines));

        int width = lines[0].length();
        int height = lines.size();
        levelSize = Vector2f(width, height);

        char mapData[width][height];

        //Create a 2D array of all the characters
        for (int y=0; y<height; ++y)
            for (int x=0; x<width; ++x)
                mapData[x][y] = lines[y][x];

        //Iterate over the 2D array again and create objects when appropriate
        for (int y=0; y<height; ++y) {
            for (int x=0; x<width; ++x) {
                if (mapData[x][y] == 'd') {
                    //Create a door to the indicated level
                    addEntity(shared_ptr<Door>{new Door(Vector2f(x, y) * BLOCK_SIZE, mapData[x][y+1])});
                    mapData[x][y+1] = '.';
                } else if (mapData[x][y] == 'p') {
                    //Place the player here if it came from the indicated level
                    if (mapData[x][y+1] == src) {
                        Vector2f pos = Vector2f(x, y + 2) * BLOCK_SIZE;
                        pos.y = pos.y - player->getCollisionBox().height;
                        player->setPosition(pos);
                        player->setOldPosition(pos);
                    }
                    mapData[x][y+1] = '.';
                }
                else
                    createObject(mapData[x][y], Vector2f(x, y));
            }
        }

        //Set up collisions
        colManager.addCollidable(plyr);
        colManager.addHandler<Player, Block>(&CollisionHandlers::PlayerBlockHandler);
        colManager.addHandler<Player, Door>(&CollisionHandlers::PlayerDoorHandler);
        colManager.addHandler<Beam, Block>(&CollisionHandlers::BeamBlockHandler);
        colManager.addHandler<Projectile, Block>(&CollisionHandlers::ProjectileBlockHandler);
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

void Level::addLevelObject(std::shared_ptr<ILevelObject> lvlObj) {
    objects.push_front(lvlObj);
}

void Level::addCollidable(std::shared_ptr<ICollidable> coll) {
    colManager.addCollidable(coll);
}

void Level::addEntity(shared_ptr<Entity> ent) {
    addLevelObject(ent);
    addCollidable(ent);
}

void Level::removeLevelObject(std::shared_ptr<ILevelObject> lvlObj) {
    objects.remove(lvlObj);
}

void Level::removeCollidable(std::shared_ptr<ICollidable> coll) {
    colManager.removeCollidable(coll);
}

void Level::removeEntity(shared_ptr<Entity> ent) {
    removeLevelObject(ent);
    removeCollidable(ent);
}

void Level::update(Time delta) {
    for (shared_ptr<ILevelObject> obj : objects) {
        obj->update(*this, delta);
    }
    player->update(*this, delta);

    colManager.processCollisions(*this);
}

void Level::draw(RenderTarget& target, RenderStates states) const {
    for (shared_ptr<ILevelObject> obj : objects) {
        target.draw(*obj);
    }
    target.draw(*player);
}
