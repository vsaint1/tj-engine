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

        void loadMusic(const std::string& _name, const std::string& _path);

        sf::Texture& getTexture(const std::string& _name) {
            return this->textures.at(_name);
        }

        sf::Font& getFont(const std::string& _name) {
            return this->fonts.at(_name);
        }

        sf::Music& getMusic(const std::string& _name) {

            return this->musics.at(_name);
        }
        void removeTexture(const std::string& _name) {
            this->textures.erase(_name);
        }

        void removeFont(const std::string& _name) {
            this->fonts.erase(_name);
        }

        void removeMusic(const std::string& _name) {
            this->musics.erase(_name);
        }

        std::string getAssetsFolder();

    private:
        std::map<std::string, sf::Texture> textures;

        std::map<std::string, sf::Font> fonts;

        std::map<std::string, sf::Music> musics;

        static AssetsManager* instance;

        tj::Debug& LOGGER = tj::Debug::geInstance();
    };

}; // namespace tj

#endif // ASSET_MANAGER_H
