#include <iostream>
#include <algorithm>
#include <utility>
#include "CollisionHandlers.h"
#include "Player.h"
#include "Block.h"
#include "Door.h"
#include "Beam.h"

using namespace sf;

void CollisionHandlers::PlayerBlockHandler(ICollidable& p, ICollidable& b) {
    //Objects may no longer be colliding, so double check
    if (!p.isCollidingWith(b))
        return;

    Player& player = dynamic_cast<Player&>(p);
    Block& block = dynamic_cast<Block&>(b);

    FloatRect playerBox = player.getCollisionBox();
    FloatRect blockBox = block.getCollisionBox();

    //Calculate the best (shortest) distance and direction to move the player so that it is out of the block
    Vector2f left(-1, 0);
    Vector2f right(1, 0);
    Vector2f up(0, -1);
    Vector2f down(0, 1);

    std::pair<float, Vector2f> dirs[4];
    dirs[0] = std::make_pair((playerBox.left + playerBox.width) - blockBox.left, left);
    dirs[1] = std::make_pair((blockBox.left + blockBox.width) - playerBox.left, right);
    dirs[2] = std::make_pair((playerBox.top + playerBox.height) - blockBox.top, up);
    dirs[3] = std::make_pair((blockBox.top + blockBox.height) - playerBox.top, down);

    auto bestDir = *std::min_element(begin(dirs), end(dirs),
            [](const std::pair<float, Vector2f>& a, const std::pair<float, Vector2f>& b){ return a.first < b.first; });

    //If the player needs to be moved up, it collided with a block below it, so it is no longer airborne
    if (bestDir.second == up)
        player.setAirborne(false);

    //Move player out of block
    player.setPosition(player.getPosition() + (bestDir.first * bestDir.second));
}

void CollisionHandlers::PlayerDoorHandler(ICollidable& p, ICollidable& d) {
    //Objects may no longer be colliding, so double check
    if (!p.isCollidingWith(d))
        return;

    Door& door = dynamic_cast<Door&>(d);
    door.setActivated(true);
}

void CollisionHandlers::BeamBlockHandler(ICollidable& be, ICollidable& bl) {
    //Objects may no longer be colliding, so double check
    if (!be.isCollidingWith(bl))
        return;

    Beam& beam = dynamic_cast<Beam&>(be);

    beam.move(beam.trace(bl) - beam.getSize().x);
}
