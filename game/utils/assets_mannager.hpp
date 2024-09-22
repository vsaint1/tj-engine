#ifndef ASSET_MANNAGER_HPP
#define ASSET_MANNAGER_HPP

#include "platform_utils.hpp"

namespace tj {

class AssetsManager {

public:
    AssetsManager() = delete;

    AssetsManager(const AssetsManager &) = delete;

    static std::string getAssetsFolder() { return tj::PlatformUtility::isMobile() ? "" : "assets/"; }
};

}; // namespace tj

#endif // ASSET_MANNAGER_HPP
