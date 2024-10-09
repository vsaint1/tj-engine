#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include "../pch.h"

enum EBatteryLevel{

    EBAT_UNKNOWN = 0,

};

namespace tj {

    class SystemInfo {

    public:
        void operator=(const SystemInfo&) = delete;


        static std::string GetDeviceName();

        static std::string GetDeviceModel();

        static std::string GetDeviceUniqueIdentifier();

        // 0.0 -> 1.0
        static float GetBatteryLevel();


    private:
        SystemInfo()                      = default;

    };

}; // namespace tj

#endif // SYSTEM_INFO_H
