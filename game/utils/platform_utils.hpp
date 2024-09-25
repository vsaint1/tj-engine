
#ifndef PLATFORM_UTILS_HPP
#define PLATFORM_UTILS_HPP

#include "../pch.hpp"

namespace tj {

enum EPlatform { EPLAT_WINDOWS, EPLAT_ANDROID, EPLAT_IOS, EPLAT_UNKNOWN };

class PlatformUtility {

  public:
    PlatformUtility() = delete;

    PlatformUtility(const PlatformUtility &) = delete;

    static EPlatform platform() {
#if defined(_WIN32)
        return EPlatform::EPLAT_WINDOWS;
#elif __IPHONEOS__
        return EPlatform::EPLAT_IOS;
#elif __ANDROID__
        return EPlatform::EPLAT_ANDROID;
#else
        return EPlatform::EPLAT_UNKNOWN;
#endif
    }

    static bool isMobile() { return platform() == EPlatform::EPLAT_IOS || platform() == EPlatform::EPLAT_ANDROID; }

    static std::string plaftorm() {
        switch (platform()) {
        case EPlatform::EPLAT_WINDOWS:
            return "Windows";
        case EPlatform::EPLAT_ANDROID:
            return "Android";
        case EPlatform::EPLAT_IOS:
            return "iOS";
        default:
            return "Unknown";
        }
    }
    
    static bool isAndroid() { return platform() == EPlatform::EPLAT_ANDROID ? true : false; }

    static bool isIOS() { return platform() == EPlatform::EPLAT_IOS ? true : false; }

    static sf::FloatRect getSafeAreaView(const glm::vec2 &windowSize) {
        float MOBILE_PADDING = isMobile() ? 20.0f : 0.0f;
        float left = MOBILE_PADDING;
        float top = MOBILE_PADDING;
        float width = windowSize.x - 2 * MOBILE_PADDING;
        float height = windowSize.y - 2 * MOBILE_PADDING;

        return sf::FloatRect(left, top, width, height);
    }
};

} // namespace tj

#endif // PLATFORM_UTILS_HPP
