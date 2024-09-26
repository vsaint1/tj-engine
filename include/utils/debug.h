#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../pch.h"

enum ELogLevel { ELOG_INFO, ELOG_WARN, ELOG_ERROR };

namespace tj {

    class Debug {
    public:
        Debug()                      = default;
        void operator=(const Debug&) = delete;

        static Debug& geInstance();

        void logInfo(const char* _format, ...);

        void logWarn(const char* _format, ...);

        void logError(const char* _format, ...);

        void setEnabled(bool _enabled) {
            bEnabled = _enabled;
        }

    private:
        std::mutex mutex;
        static Debug* instance;
        ELogLevel logLevel;
        bool bEnabled;

        void log(const char* _format, va_list _args, ELogLevel _level);
    };

}; // namespace tj

#endif // LOGGER_HPP
