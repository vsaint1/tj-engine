#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../pch.hpp"
enum  ELogLevel { ELOG_INFO, ELOG_WARN, ELOG_ERROR };

namespace tj {

    class Debug {
    public:
        Debug()                      = default;
        void operator=(const Debug&) = delete;

        static Debug& geInstance() {
            static Debug instance;
            return instance;
        }

        void logInfo(const char* _format, ...) {
            va_list args;
            va_start(args, _format);
            this->log(_format, args, ELogLevel::ELOG_INFO);
            va_end(args);
        }

        void logWarn(const char* _format, ...) {
            va_list args;
            va_start(args, _format);
            this->log(_format, args, ELogLevel::ELOG_WARN);
            va_end(args);
        }

        void logError(const char* _format, ...) {
            va_list args;
            va_start(args, _format);
            this->log(_format, args, ELogLevel::ELOG_ERROR);
            va_end(args);
        }

    private:
        std::mutex mutex;
        static Debug* instance;
        ELogLevel logLevel;

        void log(const char* _format, va_list _args, ELogLevel _level) {
            std::lock_guard<std::mutex> lock(mutex);

#ifdef __ANDROID__

            int androidLogLevel;
            switch (_level) {
            case ELogLevel::ELOG_INFO:
                androidLogLevel = ANDROID_LOG_INFO;
                break;
            case ELogLevel::ELOG_WARN:
                androidLogLevel = ANDROID_LOG_WARN;
                break;
            case ELogLevel::ELOG_ERROR:
                androidLogLevel = ANDROID_LOG_ERROR;
                break;
            }

            __android_log_vprint(androidLogLevel, LOG_TAG, _format, _args);
            __android_log_print(androidLogLevel, LOG_TAG, "\n");
#else
            const char* colorCode;
            switch (_level) {
                case ELogLevel::ELOG_INFO:
                colorCode = COLOR_CYAN;
                break;
            case ELogLevel::ELOG_WARN:
                colorCode = COLOR_YELLOW;
                break;
            case ELogLevel::ELOG_ERROR:
                colorCode = COLOR_RED;
                break;
            }

            printf("%s%s - ",colorCode, LOG_TAG);
            vprintf(_format, _args);
            printf("%s\n", COLOR_RESET);
#endif
        }
    };

}; // namespace tj

#endif // LOGGER_HPP
