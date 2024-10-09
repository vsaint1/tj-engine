#include "sys/SystemInfo.h"

// COMMENT: Injected functions means that will be available at RUNTIME based on the device running.
extern "C" {
const char* DeviceName_Injected();
const char* DeviceModel_Injected();
const char* DeviceUniqueIdentifier_Injected();
float DeviceBatteryLevel_Injected();
}


namespace tj {

    std::string SystemInfo::GetDeviceName() {

        const char* name = DeviceName_Injected();

        if (name == nullptr) {
            return "UNKNOWN_NAME";
        }

        return std::string(name);
    }

    std::string SystemInfo::GetDeviceUniqueIdentifier() {

        const char* deviceUID = DeviceUniqueIdentifier_Injected();

        if (deviceUID == nullptr) {
            return "UNKNOWN_DEVICE_UID";
        }

        return std::string(deviceUID);
    }

    std::string SystemInfo::GetDeviceModel() {
        const char* model = DeviceModel_Injected();

        if (model == nullptr) {
            return "UNKNOWN_DEVICE_MODEL";
        }

        return std::string(model);
    }

    float SystemInfo::GetBatteryLevel() {

        float battery = DeviceBatteryLevel_Injected();

        // we dont have permission or running on computer without battery.
        if (isinf(battery)) {

            return -1;
        }

        return battery;
    }

} // namespace tj
