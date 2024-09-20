# TapJoy :dash:

## Description

TapJoy is a `CMAKE` and `SFML` project "framework" used to help create games for Windows and Mobile. 

> The goals are supporting only the following platforms: Windows, Android and iOS.


## Overview

Windows distributables are built with `Visual Studio 2022 (MSVC)`, 
`Android Studio` (Android) and iOS `Xcode`.

> Current supported platforms are:
- [x] Windows
- [x] Android
- [ ] iOS 


## Dependencies

> The rar file contains the following dependencies, extract it to `dependencies` folder.

- SFML [2.6.x](https://www.sfml-dev.org/)
- GLM [1.0.x](https://github.com/g-truc/glm)
- JSON [3.11.x](https://github.com/nlohmann/json)


## Development and build

- Required tools and toolchains for each platform:

### Windows

- Visual Studio [2022](https://visualstudio.microsoft.com/)
    - C++ [C++ 20](https://en.cppreference.com/w/cpp)
    - MSVC [17.11.0](https://en.wikipedia.org/wiki/MSVC)

### Android 

> Tested on Android emulator used Pixel 8 API 30 and Samsung Galaxy A15

- Android Studio [4.1.x](https://developer.android.com/studio/)
    - Androi SDK [34.x](https://developer.android.com/studio/)
    - Android NDK [25.x](https://developer.android.com/ndk/downloads/)
    - Android Command-Line Tools [16.x](https://developer.android.com/studio/command-line)

### iOS 
- Xcode [14.x](https://developer.apple.com/xcode/)
    - TODO

### General

- Tooling
    - Git [2.45.2](https://git-scm.com/)
    - CMake [3.21.x](https://cmake.org/)
    - Vscode [1.93](https://code.visualstudio.com/)

# Code Style

This project follows [UE Coding Guidelines](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine) even though `SFML` uses camelCase for naming conventions.

> Project Under-development :warning: