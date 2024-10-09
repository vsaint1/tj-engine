#include "utils/Debug.h"


namespace tj {

    Debug& Debug::GetInstance() {
        static Debug instance;
        return instance;
    }

    void Debug::LogInfo(const char* _context, const char* _format, ...) {

        va_list args;
        va_start(args, _format);
        this->Log(_context, _format, args, ELogLevel::ELOG_INFO);
        va_end(args);
    }

    void Debug::LogWarn(const char* _context, const char* _format, ...) {

        va_list args;
        va_start(args, _format);
        this->Log(_context, _format, args, ELogLevel::ELOG_WARN);
        va_end(args);
    }

    void Debug::LogError(const char* _context, const char* _format, ...) {

        va_list args;
        va_start(args, _format);
        this->Log(_context, _format, args, ELogLevel::ELOG_ERROR);
        va_end(args);
    }

    // TODO: we write to disk the logs
    void Debug::Log(const char* _context, const char* _format, va_list _args, ELogLevel _level) {

        
        if (!bEnabled) {
            return;
        }

        sf::Lock lock(mutex);

        time_t rawtime;
        struct tm* timeinfo;
        char timeStr[20];

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

        char formatted_message[1024];
        snprintf(formatted_message, sizeof(formatted_message), "[%s][%s] - %s", timeStr, _context, _format);

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
        __android_log_vprint(androidLogLevel, LOG_TAG, formatted_message, _args);
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

        printf("%s ", colorCode);
        vprintf(formatted_message, _args);
        printf("%s\n", COLOR_RESET);

        va_end(_args);
#endif
    }

} // namespace tj
