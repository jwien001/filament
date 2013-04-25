#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <unordered_map>
#include <forward_list>
#include <memory>
#include <string>
#include <typeinfo>
#include <sstream>
#include "CollisionHandlers.h"

class CollisionManager
{
    std::unordered_map<int, std::forward_list<std::shared_ptr<ICollidable>>> collidables;
    std::unordered_map<int, std::forward_list<int>> types;
    std::unordered_map<std::string, CollisionHandler> handlers;

    public:
        /**
         * Generates a key for two collision types in the form of "smaller_type-bigger_type"
         */
        static std::string getKey(int type1, int type2) {
            std::stringstream ss;
            (type1 < type2) ? ss<<type1<<"-"<<type2 : ss<<type2<<"-"<<type1;
            return ss.str();
        }

        /**
         * Adds a new object to the collision manager.
         */
        void addCollidable(std::shared_ptr<ICollidable> collidable) {
            collidables[typeid(*collidable).hash_code()].push_front(collidable);
        }

        /**
         * Removes an object from the collision manager.
         */
        void removeCollidable(std::shared_ptr<ICollidable> collidable) {
            collidables[typeid(*collidable).hash_code()].remove(collidable);
        }

        /**
         * Adds a new collision handler to the manager.
         */
        template <typename A, typename B>
        void addHandler(CollisionHandler handler) {
            std::string key = getKey(typeid(A).hash_code(), typeid(B).hash_code());
            handlers[key] = handler;
            types[typeid(A).hash_code()].push_front(typeid(B).hash_code());
        }

        /**
         * Processes all collisions for all added objects in the manager,
         * using the added handlers to process conflicts.
         */
        void processCollisions(Level& level);
};

#endif // COLLISIONMANAGER_H
