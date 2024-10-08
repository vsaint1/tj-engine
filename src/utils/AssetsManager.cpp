#include "utils/AssetsManager.h"

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

        textures.emplace(_name, _texture);
    }

    /**
     * @brief Load a music file from the assets folder
     * @param _name The name of the music
     * @param _path The path to the music file relative to the assets folder
     */
    void AssetsManager::loadMusic(const std::string& _name, const std::string& _path) {
        sf::Music _music;

        if (textures.find(_name) != textures.end()) {
            LOGGER.logWarn("Sound with this name %s already loaded", _name.c_str());
            return;
        }

        // COMMENT: We need to store dynamically allocated Music because sf::Music is not copiable
        std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

        if (!music->openFromFile(this->getAssetsFolder() + _path)) {
            LOGGER.logError("Failed to load sound: %s", _path.c_str());
            return;
        }

        musics.emplace(_name, std::move(music));
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

        fonts.emplace(_name, _font);
    }


    
    /**
     * @brief Gets the assets folder path based on the current platform.
     * 
     * @return The assets folder path.
     * 
     * @details
     * - Mobile: base path
     * - WebGL:  /
     * - Desktop: assets/
     * - Other:  /assets/
     */
    std::string AssetsManager::getAssetsFolder() {

        if (tj::PlatformUtility::isMobile()) {
            return "";
        }

        if (tj::PlatformUtility::isWebGL()) {
            return "/";
        }

        if (tj::PlatformUtility::isDesktop()) {
            return "assets/";
        }

        return "/assets/";
    }

} // namespace tj
