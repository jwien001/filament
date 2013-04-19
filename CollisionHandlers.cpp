#include "CollisionHandlers.h"
#include "Player.h"
#include "Block.h"

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
    Vector2f bestDir;
    float bestScale, testScale;

    //Left
    bestDir = Vector2f(-1, 0);
    bestScale = (playerBox.left + playerBox.width) - blockBox.left;

    //Right
    testScale = (blockBox.left + blockBox.width) - playerBox.left;
    if (testScale > 0 && testScale < bestScale) {
        bestDir = Vector2f(1, 0);
        bestScale = testScale;
    }

    //Up
    testScale = (playerBox.top + playerBox.height) - blockBox.top;
    if (testScale > 0 && testScale < bestScale) {
        bestDir = Vector2f(0, -1);
        bestScale = testScale;
    }

    //Down
    testScale = (blockBox.top + blockBox.height) - playerBox.top;
    if (testScale > 0 && testScale < bestScale) {
        bestDir = Vector2f(0, 1);
        bestScale = testScale;
    }

    //Move player out of block
    player.setPosition(player.getPosition() + (bestDir * bestScale));
}
