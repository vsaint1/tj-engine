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
- [x] iOS 
- [x] WebGL `experimental`

## Dependencies

> The rar file contains the following dependencies, extract it to `dependencies` folder.

- SFML [2.6.x](https://www.sfml-dev.org/)
- JSON [3.11.x](https://github.com/nlohmann/json)
- XML [10.0.x](https://github.com/leethomason/tinyxml2)

## Development and build

- All the `requirements` for each platform are listed below with minimal version (major, minor, patch).

### Windows

- Visual Studio [2022](https://visualstudio.microsoft.com/)
  - C++ [C++ 20](https://en.cppreference.com/w/cpp)
  - MSVC [17.11.0](https://en.wikipedia.org/wiki/MSVC)

### Android

> Tested on Android emulator, used Pixel 8 API 30 and Samsung Galaxy A15

- Android Studio [4.1.x](https://developer.android.com/studio/)
  - Androi SDK [34.x](https://developer.android.com/studio/)
  - Android NDK [25.x](https://developer.android.com/ndk/downloads/)
  - Android Command-Line Tools [16.x](https://developer.android.com/studio/command-line)

### iOS

- Xcode [15.4](https://developer.apple.com/xcode/)
  - iOS SDK [12.x](https://developer.apple.com/)

### WebGL

> Currently experimental

- Emscripten [2.0.6](https://emscripten.org/)
  - emcc [3.1.64+](https://emscripten.org/)
  - nodejs [18.20.3](https://nodejs.org/)


### General

- Tooling
  - Git [2.45.2](https://git-scm.com/)
  - CMake [3.21.x](https://cmake.org/)
  - Vscode [1.93](https://code.visualstudio.com/)

# How to build ? :construction_worker:

<img height="32" width="32" src="examples/windows.svg" alt="windows  icon">

```bat
cmake --preset=debug-windows
cmake --build build/windows --preset=windows-d
```

<img height="32" width="32" src="examples/android.svg" alt="android  icon">


```sh
cd android
gradle assembleDebug
```

<img height="32" width="32" src="examples/ios.svg" alt="iOS  icon">
  

1. Generating the `*.xcodeproj`

```sh
cmake --preset=ios-xcode

open ProjectName.xcodeproj

```

2. Linking the framework's and libraries

<img src="examples/xcode_deps.png" alt="xcode dependencies">

3. Signing and building
   - Setup the Provisioning signing for iOS
   - Choose the Device
   - Signing and building the application

<img src="examples/ios_build.png" alt="iOS running">

<img height="32" width="32" src="examples/webgl.svg" alt="WebGL  icon">

> `WebGL` build is Currently experimental

```sh
emcmake cmake --preset=rel-webgl
emmake cmake --build build/webgl --preset=webgl-r
```

# Code Style

This project follows [UE Coding Guidelines](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine) even though im using camelCase naming conventions.
