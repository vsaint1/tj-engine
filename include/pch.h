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

// SFML LIBS
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

// ANSI COLOR CODES (https://en.wikipedia.org/wiki/ANSI_escape_code)
#define COLOR_RESET  "\033[0m"
#define COLOR_CYAN   "\033[36m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RED    "\033[31m"

#if __ANDROID__
#include <android/log.h>
#define LOG_TAG "TJLOG"
#else
#define LOG_TAG "[TJLOG]"

#endif

#include "utils/debug.h"



#endif // PCH_H
