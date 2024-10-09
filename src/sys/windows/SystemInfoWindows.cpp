#include <string>

#include <windows.h>

extern "C" {

const char* DeviceName_Injected() {
    static char computerName[256];
    DWORD size = sizeof(computerName);

    if (GetComputerNameA(computerName, &size)) {
        return computerName;
    }

    return nullptr;
}

const char* DeviceModel_Injected() {

    static char model[128];
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (GetVersionEx(&osvi)) {
        snprintf(model, sizeof(model), "Windows %lu.%lu (Build %lu)", osvi.dwMajorVersion, osvi.dwMinorVersion,
            osvi.dwBuildNumber);
        return model;
    }

    return nullptr;
}

const char* DeviceUniqueIdentifier_Injected() {
    static char deviceUID[128];
    HW_PROFILE_INFO hwProfInfo;

    if (GetCurrentHwProfile(&hwProfInfo)) {
        strncpy(deviceUID, hwProfInfo.szHwProfileGuid, sizeof(deviceUID) - 1);
        deviceUID[sizeof(deviceUID) - 1] = '\0';

        return deviceUID;
    }

    return nullptr;
}

float DeviceBatteryLevel_Injected() {
    SYSTEM_POWER_STATUS sps;

    if (GetSystemPowerStatus(&sps)) {
        if (sps.BatteryLifePercent != 255) {
            return static_cast<float>(sps.BatteryLifePercent) / 100.0f;
        }
    }
    return -1.0f;
}
}
