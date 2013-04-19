#include <utility>
#include "CollisionManager.h"

using namespace std;

void CollisionManager::processCollisions() {
    //List of collisions to handle
    forward_list<tuple<CollisionHandler, shared_ptr<ICollidable>, shared_ptr<ICollidable>>> collisions;

    //For every collision type...
    for(auto iter = begin(types); iter != end(types); ++iter) {
        int type = iter->first;

        //List of types type collides with
        forward_list<int> collidesWithTypes = iter->second;

        //For each type type collides with
        for(int collidingType : collidesWithTypes) {
            //List of objects of type type
            forward_list<shared_ptr<ICollidable>> collidableForType = collidables[type];
            //List of objects of type colliding type
            forward_list<shared_ptr<ICollidable>> collidableForCollidingType = collidables[collidingType];

            //For every possible combination of the colliding objects...
            for(shared_ptr<ICollidable> collidable : collidableForType) {
                for(shared_ptr<ICollidable> collidesWith : collidableForCollidingType) {
                    if(collidable->isCollidingWith(*collidesWith)) {
                        //If they're colliding, add the collision to the list
                        collisions.push_front(make_tuple(handlers[getKey(type, collidingType)], collidable, collidesWith));
                    }
                }
            }
        }
    }

    //Process each collision by calling the collision handlers and passing the colliding objects
    for(auto col : collisions){
        get<0>(col)(*get<1>(col), *get<2>(col));
    }
}
