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
    std::vector<std::shared_ptr<ILevelObject>> objects;
    CollisionManager colManager;
    sf::Vector2f levelSize;
    std::shared_ptr<Player> player;
    char transition;

    public:
        static const float BLOCK_SIZE;

        Level(std::string levelFile);

        void update(sf::Time delta);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void setPlayer(std::shared_ptr<Player> player);
        void addEntity(std::shared_ptr<Entity> ent);

        const sf::Vector2f& getSize() const {
            return levelSize;
        }

        const char& getTransition() const {
            return transition;
        }

        void setTransition(const char& trans) {
            transition = trans;
        }

    private:
        void createObject(char c, sf::Vector2f pos);
};

#endif // LEVEL_H
