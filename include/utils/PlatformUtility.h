#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#include "../pch.h"

namespace tj {
    enum EPlatform { EPLAT_WINDOWS, EPLAT_ANDROID, EPLAT_IOS, EPLAT_WEBGL, EPLAT_UNKNOWN };

    class PlatformUtility {

    public:
        PlatformUtility() = delete;

        PlatformUtility(const PlatformUtility&) = delete;

        static EPlatform GetPlatform();

        static std::string Platform();

        static bool IsMobile() {
            return GetPlatform() == EPlatform::EPLAT_IOS || GetPlatform() == EPlatform::EPLAT_ANDROID;
        }

        static bool IsDesktop() {
            return GetPlatform() == EPlatform::EPLAT_WINDOWS;
        }

        static bool IsWebGL() {
            return GetPlatform() == EPlatform::EPLAT_WEBGL;
        }

        static bool IsAndroid() {
            return GetPlatform() == EPlatform::EPLAT_ANDROID ? true : false;
        }

        static bool IsIOS() {
            return GetPlatform() == EPlatform::EPLAT_IOS ? true : false;
        }

        static bool is64Bits() {
            return sizeof(void*) == 8;
        }

        static sf::FloatRect GetSafeAreaView(const sf::Vector2i _windowSize);
    };
} // namespace tj

#endif // PLATFORM_UTILS_H
