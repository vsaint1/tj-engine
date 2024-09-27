#include "utils/assets_manager.h"

namespace tj {

    AssetsManager& AssetsManager::getInstance() {
        static AssetsManager instance;
        return instance;
    }

    void AssetsManager::loadTexture(const std::string& _name, const std::string& _path) {
        sf::Texture _texture;

        if (textures.find(_name) != textures.end()) {
            LOGGER.logWarn("Texture with this name %s already created", _name.c_str());
            return;
        }

        if (!_texture.loadFromFile(this->getAssetsFolder() + _path)) {
            LOGGER.logError("Failed to load texture: %s", _path.c_str());
            return;
        }

        textures[_name] = _texture;
    }

    void AssetsManager::loadFont(const std::string& _name, const std::string& _path) {
        sf::Font _font;

        if (textures.find(_name) != textures.end()) {
            LOGGER.logWarn("Font with this name %s already loaded", _name.c_str());
            return;
        }

        if (!_font.loadFromFile(this->getAssetsFolder() + _path)) {
            LOGGER.logError("Failed to load font: %s", _path.c_str());
            return;
        }

        fonts[_name] = _font;
    }
} // namespace tj
