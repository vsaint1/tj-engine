#ifndef ASSET_MANNAGER_HPP
#define ASSET_MANNAGER_HPP

#include "platform_utils.hpp"

namespace tj {

    class AssetsManager {

    public:
        AssetsManager()              = default;
        void operator=(const Debug&) = delete;

        static AssetsManager& getInstance() {
            static AssetsManager instance;
            return instance;
        }

        void loadTexture(const std::string& _name, const std::string& _path) {
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

        void loadFont(const std::string& _name, const std::string& _path) {
            sf::Font _font;

            if (fonts.find(_name) != fonts.end()) {
                LOGGER.logWarn("Font with this name %s already created", _name.c_str());
                return;
            }

            if (!_font.loadFromFile(this->getAssetsFolder() + _path)) {
                LOGGER.logError("Failed to load font: %s", _path.c_str());
                return;
            }

            fonts[_name] = _font;
        }

        sf::Texture& getTexture(const std::string& _name) {
            return this->textures[_name];
        }

        sf::Font& getFont(const std::string& _name) {
            return this->fonts[_name];
        }

        void removeTexture(const std::string& _name) {
            this->textures.erase(_name);
        }

        void removeFont(const std::string& _name) {
            this->fonts.erase(_name);
        }

    private:
        std::string getAssetsFolder() {
            return tj::PlatformUtility::isMobile() ? "" : "assets/";
        }

        std::map<std::string, sf::Texture> textures;

        std::map<std::string, sf::Font> fonts;

        static AssetsManager* instance;

        tj::Debug& LOGGER = tj::Debug::geInstance();
    };

}; // namespace tj

#endif // ASSET_MANNAGER_HPP
