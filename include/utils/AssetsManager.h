#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "PlatformUtility.h"

namespace tj {

    class AssetsManager {

    public:
        void operator=(const Debug&) = delete;

        static AssetsManager& GetInstance();

        void LoadTexture(const std::string& _name, const std::string& _path);

        void LoadFont(const std::string& _name, const std::string& _path);

        void LoadMusic(const std::string& _name, const std::string& _path);

        sf::Texture& GetTexture(const std::string& _name) {
            return this->textures.at(_name);
        }

        sf::Font& GetFont(const std::string& _name) {
            return this->fonts.at(_name);
        }

        sf::Music& GetMusic(const std::string& _name) {

            return *(this->musics.at(_name));
        }

        void RemoveTexture(const std::string& _name) {
            this->textures.erase(_name);
        }

        void RemoveFont(const std::string& _name) {
            this->fonts.erase(_name);
        }

        void RemoveMusic(const std::string& _name) {
            this->musics.erase(_name);
        }

        std::string GetAssetsFolder();

    private:
        AssetsManager() = default;

        std::map<std::string, sf::Texture> textures;

        std::map<std::string, sf::Font> fonts;

        std::map<std::string, std::unique_ptr<sf::Music>> musics;

        static AssetsManager* instance;

        tj::Debug& LOGGER = tj::Debug::GetInstance();
    };

}; // namespace tj

#endif // ASSET_MANAGER_H
