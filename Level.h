#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "CollisionManager.h"

class ILevelObject;
class Entity;

class Level : public sf::Drawable
{
    static const int BLOCK_SIZE;

    std::vector<std::shared_ptr<ILevelObject>> objects;
    CollisionManager colManager;
    sf::Vector2f levelSize;

    public:
        Level(std::string levelFile);

        void update(sf::Time delta);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void addEntity(std::shared_ptr<Entity> obj);

        const sf::Vector2f& getSize() const {
            return levelSize;
        }

    private:
        void createObject(char c, sf::Vector2f pos);
};

#endif // LEVEL_H
