#include "sys/system_info.h"

// ensure this are valid at runtime.
extern "C" {
const char* deviceName();
const char* deviceModel();
const char* deviceUniqueIdentifier();
float deviceBatteryLevel();
}


namespace tj {

    const char* SystemInfo::getDeviceName() {

        const char* name = deviceName();

        if (name == nullptr) {
            return "UNKNOWN_NAME";
        }

        return name;
    }

    const char* SystemInfo::getDeviceUniqueIdentifier() {

        const char* deviceUID = deviceUniqueIdentifier();

        if (deviceUID == nullptr) {
            return "UNKNOWN_DEVICE_UID";
        }

        return deviceUID;
    }

    const char* SystemInfo::getDeviceModel() {
        const char* model = deviceModel();

        if (model == nullptr) {
            return "UNKNOWN_DEVICE_MODEL";
        }

        return model;
    }

    float SystemInfo::getBatteryLevel() {

        float battery = deviceBatteryLevel();

        // we dont have permission or running on computer without battery.
        if (isinf(battery)) {

            return -1;
        }

        return battery;
    }

} // namespace tj
