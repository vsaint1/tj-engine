#ifndef PCH_H
#define PCH_H


// STD LIBS
#include <cstdarg>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

// SFML LIBS
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

// ANSI COLOR CODES (https://en.wikipedia.org/wiki/ANSI_escape_code)
#if defined(_WIN32) || defined(__ANDROID__)
#define COLOR_RESET  "\033[0m"
#define COLOR_CYAN   "\033[36m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RED    "\033[31m"
#else
#define COLOR_RESET  ""
#define COLOR_CYAN   ""
#define COLOR_YELLOW ""
#define COLOR_RED    ""
#endif

#if defined(__ANDROID__)
#include <android/log.h>
#define LOG_TAG "TJLOG"
#else
#define LOG_TAG "[TJLOG]"
#endif

#define LOG_CONTEXT_FILE (std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__)).c_str()

#include "utils/Debug.h"

#define TJ_LOG_INFO(format, ...)  tj::Debug::GetInstance().LogInfo(LOG_CONTEXT_FILE, format, ##__VA_ARGS__)
#define TJ_LOG_WARN(format, ...)  tj::Debug::GetInstance().LogWarn(LOG_CONTEXT_FILE, format, ##__VA_ARGS__)
#define TJ_LOG_ERROR(format, ...) tj::Debug::GetInstance().LogError(LOG_CONTEXT_FILE, format, ##__VA_ARGS__)



#ifdef _WIN64 
    #define TJ_API __declspec(dllexport)
#elif __APPLE__ || __linux__
    #define TJ_API __attribute__((visibility("default")))
#else 
#define TJ_API
#endif

#endif // PCH_H
