#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "CollisionManager.h"

class ILevelObject;
class Entity;
class Player;

class Level : public sf::Drawable
{
    char id;
    std::forward_list<std::shared_ptr<ILevelObject>> objects;
    CollisionManager colManager;
    sf::Vector2f levelSize;
    std::shared_ptr<Player> player;
    char destination;
    sf::Vector2f mousePos;

    public:
        static const float BLOCK_SIZE;

        Level(char level, std::shared_ptr<Player> player, char src = '\0');

        void update(sf::Time delta);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void addLevelObject(std::shared_ptr<ILevelObject> lvlObj);
        void addCollidable(std::shared_ptr<ICollidable> coll);
        void addEntity(std::shared_ptr<Entity> ent);

        void removeLevelObject(std::shared_ptr<ILevelObject> lvlObj);
        void removeCollidable(std::shared_ptr<ICollidable> coll);

        const sf::Vector2f& getSize() const {
            return levelSize;
        }

        const char& getId() const {
            return id;
        }

        const char& getDestination() const {
            return destination;
        }

        void setDestination(const char& dest) {
            destination = dest;
        }

        const sf::Vector2f& getMouse() const {
            return mousePos;
        }

        void setMouse(const sf::Vector2f& mouse) {
            mousePos = mouse;
        }

    private:
        void createObject(char c, sf::Vector2f pos);
};

#endif // LEVEL_H
