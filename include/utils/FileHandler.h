#ifndef FILEREADER_H
#define FILEREADER_H


#include "pch.h"
#include "utils/AssetsManager.h"
#include "utils/TinyXml.h"

#include "utils/Json.hpp"


namespace tj {

    class FileHandler : public sf::FileInputStream {
    public:
        FileHandler(const std::string& filename) : filename(filename) {
            if (!open(assetsManager.GetAssetsFolder() + filename)) {
                TJ_LOG_ERROR("Failed to open file: %s", filename.c_str());
                throw std::runtime_error("Failed to open file: " + filename);
            }

            fileSize = this->getSize();

            if (fileSize <= 0) {
                TJ_LOG_ERROR("The file has no content: %s", filename.c_str());
                throw std::runtime_error("File has no content: " + filename);
            }
        }

        nlohmann::json ReadJson(sf::Uint8 _identation = 4);

        // COMMENT: since tinyxml2 doesnt support copy ctor
        std::unique_ptr<tinyxml2::XMLDocument> ReadXml();

        // TODO: make overwrite option
        static bool SaveFileToDisk(const std::string& _filename, std::string _content, bool _overwrite = false);

    private:
        std::string filename;
        sf::Int64 fileSize{0};

        FileHandler(const FileHandler&)            = delete;
        FileHandler& operator=(const FileHandler&) = delete;

        tj::AssetsManager& assetsManager = tj::AssetsManager::GetInstance();
    };
} // namespace tj
#endif // FILEREADER_H
