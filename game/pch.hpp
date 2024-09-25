#ifndef PC_HPP
#define PC_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <unordered_map>
#include <memory>
#include <random>
#include <cstdarg>

#if __ANDROID__
#include <android/log.h>
#define LOG_TAG "TJLOG"
#else
#define LOG_TAG "[TJLOG]"
#endif

#include "utils/debug.hpp"


#endif // PC_HPP
