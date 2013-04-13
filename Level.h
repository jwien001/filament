#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "ILevelObject.h"

using namespace sf;

class ILevelObject;

class Level : public Drawable
{
    std::vector<std::shared_ptr<ILevelObject>> objects;

    public:
        Level();

        void update(Time delta);
        void draw(RenderTarget& target, RenderStates states) const;
};

#endif // LEVEL_H
