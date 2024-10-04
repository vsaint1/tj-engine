
#include "utils/PlatformUtility.h"


namespace tj {


    EPlatform PlatformUtility::platform() {

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

    std::string PlatformUtility::plaftorm() {
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

    sf::FloatRect PlatformUtility::getSafeAreaView(const sf::Vector2i _windowSize) {


        float MOBILE_PADDING = isMobile() ? 20.0f : 0.0f;
        float left           = MOBILE_PADDING;
        float top            = MOBILE_PADDING;
        float width          = _windowSize.x - 2 * MOBILE_PADDING;
        float height         = _windowSize.y - 2 * MOBILE_PADDING;

        return sf::FloatRect(left, top, width, height);
    }


} // namespace tj
