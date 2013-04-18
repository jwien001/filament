#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "ILevelObject.h"

class ILevelObject;

class Level : public sf::Drawable
{
    std::vector<std::shared_ptr<ILevelObject>> objects;

    public:
        Level();

        void update(sf::Time delta);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // LEVEL_H
