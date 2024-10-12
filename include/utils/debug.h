#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../pch.h"

enum ELogLevel { ELOG_INFO, ELOG_WARN, ELOG_ERROR };

namespace tj {

    class Debug {
    public:
        void operator=(const Debug&) = delete;

        static Debug& GetInstance();

        void LogInfo(const char* _context, const char* _format, ...);

        void LogWarn(const char* _context, const char* _format, ...);

        void LogError(const char* _context, const char* _format, ...);


        void SetEnabled(bool _enabled) {
            bEnabled = _enabled;
        }

        void SetSaveToDisk(bool _enabled) {
            bSaveToDisk = _enabled;
        }

        std::vector<std::string>& GetLogBuffer() {
            return this->logBuffer;
        }

    private:
        Debug() = default;

        sf::Mutex mutex;
        static Debug* instance;
        ELogLevel logLevel;
        bool bEnabled    = true;
        bool bSaveToDisk = false;
        std::vector<std::string> logBuffer;

        void Log(const char* _context, const char* _format, va_list _args, ELogLevel _level);
    };

}; // namespace tj


#endif // LOGGER_HPP
