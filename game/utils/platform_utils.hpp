
#ifndef PLATFORM_UTILS_HPP
#define PLATFORM_UTILS_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#if __ANDROID__ || __IPHONEOS__
#define ASSETS_FOLDER ""
#else
#define ASSETS_FOLDER "assets/"
#endif

namespace tp {

enum EPlatform { PLAT_WINDOWS, PLAT_ANDROID, PLAT_IOS, PLAT_UNKNOWN };

class PlatformUtility {

  public:
    PlatformUtility() = delete;

    PlatformUtility(const PlatformUtility &) = delete;

    static EPlatform platform() {
#if defined(_WIN32)
        return EPlatform::PLAT_WINDOWS;
#elif __IPHONEOS__
        return EPlatform::PLAT_IOS;
#elif __ANDROID__
        return EPlatform::PLAT_ANDROID;
#else
        return EPlatform::PLAT_UNKNOWN;
#endif
    }

    static bool isMobile() { return platform() == EPlatform::PLAT_IOS || platform() == EPlatform::PLAT_ANDROID; }

    static std::string assetsFolder() { return ASSETS_FOLDER; }

    static std::string plaftorm() {
        switch (platform()) {
        case EPlatform::PLAT_WINDOWS:
            return "Windows";
        case EPlatform::PLAT_ANDROID:
            return "Android";
        case EPlatform::PLAT_IOS:
            return "iOS";
        default:
            return "Unknown";
        }
    }

    static sf::FloatRect getSafeAreaView(const glm::vec2 &windowSize) {
        float MOBILE_PADDING = isMobile() ? 20.0f : 0.0f; 
        float left = MOBILE_PADDING;
        float top = MOBILE_PADDING;
        float width = windowSize.x - 2 * MOBILE_PADDING;
        float height = windowSize.y - 2 * MOBILE_PADDING;

        return sf::FloatRect(left, top, width, height);
    }
};

} // namespace tp

#endif // PLATFORM_UTILS_HPP
