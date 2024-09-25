#ifndef PC_HPP
#define PC_HPP

#include <cstdarg>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

// Ansi color codes
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

#include "utils/debug.hpp"


#endif // PC_HPP
