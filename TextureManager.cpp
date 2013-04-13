#include <iostream>

#include "TextureManager.h"

using namespace sf;

TextureManager texManager;

Texture* TextureManager::load(const std::string& strId) {
    Texture* tex = new Texture();
    if (!tex->loadFromFile(strId)) {
        std::cout << "[WARN] TextureManager failed to load: " << strId << std::endl;
        delete tex;
        tex = NULL;
    }

    return tex;
}
