
#include "utils/PlatformUtility.h"


namespace tj {


    EPlatform PlatformUtility::GetPlatform() {

#if defined(_WIN32)
        return EPlatform::EPLAT_WINDOWS;
#elif __IPHONEOS__
        return EPlatform::EPLAT_IOS;
#elif __ANDROID__
        return EPlatform::EPLAT_ANDROID;
#elif __EMSCRIPTEN__
        return EPlatform::EPLAT_WEBGL;
#else
        return EPlatform::EPLAT_UNKNOWN;
#endif
    }

    std::string PlatformUtility::Platform() {
        switch (GetPlatform()) {
        case EPlatform::EPLAT_WINDOWS:
            return "Windows";
        case EPlatform::EPLAT_ANDROID:
            return "Android";
        case EPlatform::EPLAT_IOS:
            return "iOS";
        case EPlatform::EPLAT_WEBGL:
            return "WebGL";
        default:
            return "Unknown";
        }
    }

    sf::FloatRect PlatformUtility::GetSafeAreaView(const sf::Vector2i _windowSize) {


        float MOBILE_PADDING = IsMobile() ? 20.0f : 0.0f;
        float left           = MOBILE_PADDING;
        float top            = MOBILE_PADDING;
        float width          = _windowSize.x - 2 * MOBILE_PADDING;
        float height         = _windowSize.y - 2 * MOBILE_PADDING;

        return sf::FloatRect(left, top, width, height);
    }


} // namespace tj
