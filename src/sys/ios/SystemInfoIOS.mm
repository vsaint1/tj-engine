#include "Foundation/Foundation.h"
#include "UIKit/UIKit.h"


extern "C"{

    const char* deviceName() {
        NSString *deviceName = [[UIDevice currentDevice] name];
        return [deviceName UTF8String];
    }

    const char* deviceModel(){
        NSString *deviceModel = [[UIDevice currentDevice] model];
        return [deviceModel UTF8String];
    }

    const char* deviceUniqueIdentifier() {
        NSUUID *deviceUUID = [[UIDevice currentDevice] identifierForVendor];
        NSString *uuidString = [deviceUUID UUIDString];
        return [uuidString UTF8String];
    }


    float deviceBatteryLevel(){
        float deviceBattery = [[UIDevice currentDevice] batteryLevel];
        
        return deviceBattery;
    }

}
