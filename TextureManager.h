#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

using namespace sf;

class TextureManager : public ResourceManager<Texture>
{
    protected:
        virtual Texture* load(const std::string& strId);
};

extern TextureManager texManager;

#endif // TEXTUREMANAGER_H
