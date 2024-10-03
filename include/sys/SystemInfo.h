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


        static const char* getDeviceName();

        static const char* getDeviceModel();

        static const char* getDeviceUniqueIdentifier();

        // 0.0 -> 1.0
        static float getBatteryLevel();


    private:
        SystemInfo()                      = default;

    };

}; // namespace tj

#endif // SYSTEM_INFO_H
