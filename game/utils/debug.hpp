#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../pch.hpp"
namespace tj {

class Debug {

  public:
    static void logInfo(const char *format, ...) {
        va_list args;
        va_start(args, format);

#ifdef __ANDROID__
        __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, format, args);
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "\n");
#else
        printf("%s - ", LOG_TAG);
        vprintf(format, args);
        printf("\n");
#endif

        va_end(args);
    }
};
}; // namespace tj

#endif // LOGGER_HPP
