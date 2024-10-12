#include "utils/FileHandler.h"


namespace tj {


    nlohmann::json FileHandler::ReadJson(sf::Uint8 _identation) {

        std::string fileContent(fileSize, '\0');
        if (read(&fileContent[0], fileSize) != fileSize) {
            TJ_LOG_ERROR("Error while reading file: %s", filename.c_str());
            throw std::runtime_error("Error reading file: " + filename);
        }

        nlohmann::json jsonObject;
        try {
            jsonObject = nlohmann::json::parse(fileContent);
        } catch (const nlohmann::json::parse_error& e) {
            TJ_LOG_ERROR("JSON parsing error in file %s: %s", filename.c_str(), e.what());
            throw;
        }

        return jsonObject;
    }

    std::unique_ptr<tinyxml2::XMLDocument> FileHandler::ReadXml() {

        std::string fileContent(fileSize, '\0');

        if (read(&fileContent[0], fileSize) != fileSize) {
            TJ_LOG_ERROR("Error while reading file: %s", filename.c_str());
            throw std::runtime_error("Error reading file: " + filename);
        }

        auto doc                  = std::make_unique<tinyxml2::XMLDocument>();
        tinyxml2::XMLError result = doc->Parse(fileContent.c_str(), fileSize);

        if (result != tinyxml2::XML_SUCCESS) {
            TJ_LOG_ERROR("XML parsing error in file %s: %s", filename.c_str(), doc->ErrorStr());
            throw std::runtime_error("Failed to parse XML file: " + filename);
        }


        return doc;
    }

    bool FileHandler::SaveFileToDisk(const std::string& _filename, std::string _content, bool _overwrite) {


        std::ofstream ofFile(_filename);

        if (std::filesystem::exists(_filename)) {
            TJ_LOG_ERROR("File already exists: %s", _filename.c_str());
            return false;
        }


        if (!ofFile.is_open()) {
            TJ_LOG_ERROR("Failed to create a file: %s", _filename.c_str());
            return false;
        }

        ofFile << _content;

        ofFile << std::endl;

        ofFile.close();

        return true;
    }

} // namespace tj
