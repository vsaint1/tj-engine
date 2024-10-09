#include "utils/AssetsManager.h"

namespace tj {

    AssetsManager& AssetsManager::GetInstance() {
        static AssetsManager instance;
        return instance;
    }

    void AssetsManager::LoadTexture(const std::string& _name, const std::string& _path) {

        if (textures.find(_name) != textures.end()) {
            LOGGER.LogWarn("Texture with this name %s already created", _name.c_str());
            return;
        }

        std::unique_ptr <sf::Texture> texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(this->GetAssetsFolder() + _path)) {
            LOGGER.LogError("Failed to load texture: %s", _path.c_str());
            return;
        }

        textures.emplace(_name, std::move(texture));
    }

    /**
     * @brief Load a music file from the assets folder
     * @param _name The name of the music
     * @param _path The path to the music file relative to the assets folder
     */
    void AssetsManager::LoadMusic(const std::string& _name, const std::string& _path) {

        if (textures.find(_name) != textures.end()) {
            LOGGER.LogWarn("Sound with this name %s already loaded", _name.c_str());
            return;
        }

        // COMMENT: We need to store dynamically allocated Music because sf::Music is not copiable
        std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

        if (!music->openFromFile(this->GetAssetsFolder() + _path)) {
            LOGGER.LogError("Failed to load sound: %s", _path.c_str());
            return;
        }

        musics.emplace(_name, std::move(music));
    }

    void AssetsManager::LoadFont(const std::string& _name, const std::string& _path) {

        if (textures.find(_name) != textures.end()) {
            LOGGER.LogWarn("Font with this name %s already loaded", _name.c_str());
            return;
        }

        std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();

        if (!font->loadFromFile(this->GetAssetsFolder() + _path)) {
            LOGGER.LogError("Failed to load font: %s", _path.c_str());
            return;
        }

        fonts.emplace(_name, std::move(font));
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
    std::string AssetsManager::GetAssetsFolder() {

        if (tj::PlatformUtility::IsMobile()) {
            return "";
        }

        if (tj::PlatformUtility::IsWebGL()) {
            return "/";
        }

        if (tj::PlatformUtility::IsDesktop()) {
            return "assets/";
        }

        return "/assets/";
    }

} // namespace tj
