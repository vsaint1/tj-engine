#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#include "../pch.h"

namespace tj {
    enum EPlatform { EPLAT_WINDOWS, EPLAT_ANDROID, EPLAT_IOS, EPLAT_WEBGL, EPLAT_UNKNOWN };

    class PlatformUtility {

    public:
        PlatformUtility() = delete;

        PlatformUtility(const PlatformUtility&) = delete;

        static EPlatform platform();

        static std::string plaftorm();

        static bool isMobile() {
            return platform() == EPlatform::EPLAT_IOS || platform() == EPlatform::EPLAT_ANDROID || EPlatform::EPLAT_WEBGL;
        }


        static bool isAndroid() {
            return platform() == EPlatform::EPLAT_ANDROID ? true : false;
        }

        static bool isIOS() {
            return platform() == EPlatform::EPLAT_IOS ? true : false;
        }

        static sf::FloatRect getSafeAreaView(const sf::Vector2i _windowSize);

    };
} // namespace tj

#endif // PLATFORM_UTILS_H
