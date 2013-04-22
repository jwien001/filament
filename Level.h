#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "ILevelObject.h"
#include "Entity.h"
#include "CollisionManager.h"

class ILevelObject;
class Entity;

class Level : public sf::Drawable
{
    std::vector<std::shared_ptr<ILevelObject>> objects;
    CollisionManager colManager;

    public:
        Level();

        void update(sf::Time delta);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void addEntity(std::shared_ptr<Entity> obj);
};

#endif // LEVEL_H
