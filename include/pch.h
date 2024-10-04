#ifndef PCH_H
#define PCH_H


// STD LIBS
#include <cstdarg>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <ctime>
#include <iomanip>
#include <fstream>

// SFML LIBS
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

#define LOG_CONTEXT_FILE (std::string(__FILE__) + ":" + std::to_string(__LINE__)).c_str() 

#include "utils/Debug.h"



#endif // PCH_H
