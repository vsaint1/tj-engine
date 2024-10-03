#include <android/native_activity.h>
#include <sstream>

#include <SFML/System/NativeActivity.hpp>

#define PROP_VALUE_MAX 92

// TODO: change from jni and get from DeviceInfo.java

extern "C" {

const char* deviceName() {


    ANativeActivity* activity = sf::getNativeActivity();
    JavaVM* vm                = activity->vm;
    JNIEnv* env               = activity->env;

    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name    = "TJNativeThread";
    attachargs.group   = nullptr;
    jint res           = vm->AttachCurrentThread(&env, &attachargs);

    if (res == JNI_ERR) {
        return nullptr;
    }

    jclass androidBuildClass = env->FindClass("android/os/Build");
    jfieldID deviceFieldID   = env->GetStaticFieldID(androidBuildClass, "DEVICE", "Ljava/lang/String;");
    if (deviceFieldID == nullptr) {
        env->DeleteLocalRef(androidBuildClass);
        return nullptr;
    }

    auto modelString = (jstring) env->GetStaticObjectField(androidBuildClass, deviceFieldID);

    if (modelString == nullptr) {
        env->DeleteLocalRef(androidBuildClass);
        return nullptr;
    }

    const char* deviceCStr = env->GetStringUTFChars(modelString, nullptr);

    if (deviceCStr != nullptr) {
        env->ReleaseStringUTFChars(modelString, deviceCStr);
        return deviceCStr;
    }

    env->DeleteLocalRef(modelString);
    env->DeleteLocalRef(androidBuildClass);
    vm->DetachCurrentThread();

    return nullptr;
}


const char* deviceModel() {

    ANativeActivity* activity = sf::getNativeActivity();
    JavaVM* vm                = activity->vm;
    JNIEnv* env               = activity->env;

    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name    = "TJNativeThread";
    attachargs.group   = nullptr;
    jint res           = vm->AttachCurrentThread(&env, &attachargs);

    if (res == JNI_ERR) {
        return nullptr;
    }

    jclass androidBuildClass = env->FindClass("android/os/Build");
    jfieldID modelFieldID    = env->GetStaticFieldID(androidBuildClass, "MODEL", "Ljava/lang/String;");
    if (modelFieldID == nullptr) {
        env->DeleteLocalRef(androidBuildClass);
        return nullptr;
    }

    auto modelString = (jstring) env->GetStaticObjectField(androidBuildClass, modelFieldID);

    if (modelString == nullptr) {
        env->DeleteLocalRef(androidBuildClass);
        return nullptr;
    }

    const char* modelCStr = env->GetStringUTFChars(modelString, nullptr);

    if (modelCStr != nullptr) {
        env->ReleaseStringUTFChars(modelString, modelCStr);
        return modelCStr;
    }

    env->DeleteLocalRef(modelString);
    env->DeleteLocalRef(androidBuildClass);
    vm->DetachCurrentThread();

    return nullptr;
}

const char* deviceUniqueIdentifier() {
    std::stringstream deviceUID;
    deviceUID << "35";

    const char* properties[] = {"ro.product.board", "ro.product.brand", "ro.product.cpu.abi", "ro.product.device",
        "ro.build.display.id", "ro.build.host", "ro.build.id", "ro.product.manufacturer", "ro.product.model",
        "ro.product.name", "ro.build.tags", "ro.product.type", "ro.build.user"};

    int segmentCount = 0;

    for (const char* property : properties) {
        char value[PROP_VALUE_MAX];
        if (__system_property_get(property, value) > 0) {
            int segment = strlen(value) % 10;
            deviceUID << segment;
        } else {
            deviceUID << "000";
        }

        if (++segmentCount % 3 == 0 && segmentCount < 13) {
            deviceUID << "-";
        }
    }

    return deviceUID.str().c_str();
}

float deviceBatteryLevel() {
    char batteryLevel[PROP_VALUE_MAX];

    return __system_property_get("battery.level", batteryLevel);
}
}
