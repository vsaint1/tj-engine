#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "PlatformUtility.h"

namespace tj {

    class AssetsManager {

    public:
        AssetsManager()              = default;
        void operator=(const Debug&) = delete;

        static AssetsManager& getInstance();

        void loadTexture(const std::string& _name, const std::string& _path);

        void loadFont(const std::string& _name, const std::string& _path);


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


        std::string getAssetsFolder() {
            return tj::PlatformUtility::isMobile() ? "" : "assets/";
        }

    private:
        std::map<std::string, sf::Texture> textures;

        std::map<std::string, sf::Font> fonts;

        static AssetsManager* instance;

        tj::Debug& LOGGER = tj::Debug::geInstance();
    };

}; // namespace tj

#endif // ASSET_MANAGER_H