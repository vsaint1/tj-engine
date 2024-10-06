cmake_minimum_required(VERSION 3.22.1)

set(APP_NAME "SuperGame")
set(APP_VERSION "0.1.0")
set(APP_IDENTIFIER "com.tj.engine")
set(NDK_VERSION "25.1.8937393")
set(CODE_SIGN_IDENTITY "iPhone Developer")
set(DEPLOYMENT_TARGET 13.0)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (${APP_NAME} VERSION ${APP_VERSION} LANGUAGES CXX)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "iOS" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    add_subdirectory(dependencies/SFML) # on iOS we don't need this, already pre-compiled on SFML-IOS folder
endif()


file(GLOB_RECURSE SOURCES_FILE src/*.cpp)

list(FILTER SOURCES_FILE EXCLUDE REGEX "src/sys/windows/.*")
list(FILTER SOURCES_FILE EXCLUDE REGEX "src/sys/ios/*.mm")
list(FILTER SOURCES_FILE EXCLUDE REGEX "src/sys/android/.*")
list(FILTER SOURCES_FILE EXCLUDE REGEX "src/sys/web/.*")
message(STATUS "Filtered source files: ${SOURCES_FILE} \n")

include_directories(${CMAKE_SOURCE_DIR}/include)

set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)


if (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(LIBS sfml-main sfml-graphics sfml-window sfml-system sfml-audio sfml-network sfml-activity)
elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(LIBS sfml-main sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set(LIBS sfml-system sfml-window sfml-graphics sfml-network sfml-audio -lfreetype -logg -lvorbis -lz)
else()
    set(LIBS sfml-main sfml-graphics sfml-window sfml-system sfml-audio sfml-network Advapi32)
endif()

set(DIST_DIR ${CMAKE_SOURCE_DIR}/dist)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")

    file(GLOB_RECURSE WIN_FILES "src/sys/windows/*.cpp")

    add_executable(${CMAKE_PROJECT_NAME} ${SOURCES_FILE} ${WIN_FILES}  ${CMAKE_SOURCE_DIR}/settings/windows/icon.rc)

    target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

    set(OUTPUT_DIR ${DIST_DIR}/windows/$<CONFIG>)


     add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
         COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${OUTPUT_DIR}
         COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> ${OUTPUT_DIR}
         COMMAND_EXPAND_LISTS
         COMMENT "Building windows distributables \n")

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_FOLDER} ${OUTPUT_DIR}/assets
        COMMENT "Copying assets to executable directory \n")

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/dependencies/SFML/extlibs/bin/x64/openal32.dll ${OUTPUT_DIR}
        COMMENT "Copying OpenAL32.dll to executable directory \n")

   
        
endif() 

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIST_DIR}/webgl)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DIST_DIR}/webgl)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${DIST_DIR}/webgl)
    file(GLOB_RECURSE WEB_FILES "src/sys/web/*.cpp")

    set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_DEBUG -g3 -gsource-map -O0)

    set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_RELEASE -O3)

    set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS
        $<$<CONFIG:Debug>:${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_DEBUG}>
        $<$<CONFIG:Release>:${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_RELEASE}>
        -pthread
        --use-port=freetype
        --use-port=ogg
        --use-port=vorbis)

    # -sEXCEPTION_STACK_TRACES=1 # Exceptions will contain stack traces and uncaught exceptions will display stack traces
    # -sGL_ASSERTIONS=1          # Adds extra checks for error situations in the GL library
    # -sDETERMINISTIC=1          # Force `Date.now()`, `Math.random`, etc. to return deterministic results
    # -fwasm-exceptions          # TODO P1: -fwasm-exceptions seems to break examples
    # -sEXCEPTION_DEBUG=1        # Print out exceptions in emscriptened code (SPEWS WARNINGS)
    # -sGL_DEBUG=1               # Enables more verbose debug printing of WebGL related operations (SPEWS WARNINGS)

    set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_DEBUG -g3 -gsource-map -sASSERTIONS=2 -sCHECK_NULL_WRITES=1 -sSAFE_HEAP=1 -sSTACK_OVERFLOW_CHECK=1)

    set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_RELEASE -O3)

    set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_ASYNCIFY -sASYNCIFY=1) #-sASYNCIFY_IGNORE_INDIRECT=1)

    set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS
        $<$<CONFIG:Debug>:${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_DEBUG}>
        $<$<CONFIG:Release>:${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_RELEASE}>

        ${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_ASYNCIFY}

        #-pthread                            # Enable threading support

        -Wno-limited-postlink-optimizations # warning: running limited binaryen optimizations because DWARF info requested (or indirectly required)
        -Wno-pthreads-mem-growth            # warning: -pthread + ALLOW_MEMORY_GROWTH may run non-wasm code slowly, see https://github.com/WebAssembly/design/issues/1271

        -sALLOW_MEMORY_GROWTH=1             # Grow the memory arrays at runtime
        -sEXIT_RUNTIME=1                    # Execute cleanup (e.g. `atexit`) after `main` completes
        -sFETCH=1                           # Enables `emscripten_fetch` API
        -sFORCE_FILESYSTEM=1                # Makes full filesystem support be included
        -sFULL_ES2=1                        # Forces support for all GLES2 features, not just the WebGL-friendly subset
        -sMAX_WEBGL_VERSION=1               # Specifies the highest WebGL version to target
        -sMIN_WEBGL_VERSION=1               # Specifies the lowest WebGL version to target
        -sSTACK_SIZE=16mb                    # Set the total stack size
        -sUSE_PTHREADS=1                    # Enable threading support
        -sWASM=1                            # Compile code to WebAssembly

        -sGL_EXPLICIT_UNIFORM_LOCATION=1  # TODO P0:
        -sGL_EXPLICIT_UNIFORM_BINDING=1   # TODO P0:

        --emrun                             # Add native support for `emrun` (I/O capture)

        # --embed-file ${CMAKE_SOURCE_DIR}/assets@/

        --preload-file ${CMAKE_SOURCE_DIR}/assets@/

        -sTOTAL_MEMORY=1024mb

        # --shell-file=${CMAKE_SOURCE_DIR}/shell.html
    )

    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/dependencies/SFML-WEB/")
    find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED)

    add_executable (${CMAKE_PROJECT_NAME} ${SOURCES_FILE} ${WEB_FILES})

    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS})
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LIBS})
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE ${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS})
  
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

endif()


# TODO: fix iOS linking libraries xcode
if(CMAKE_SYSTEM_NAME STREQUAL "iOS")

    file(GLOB_RECURSE OBJ_C_FILES "src/sys/ios/*.mm")
    set(SFML_STATIC_LIBRARIES TRUE)

    set(SFML_DIR "${CMAKE_SOURCE_DIR}/dependencies/SFML-IOS/lib/cmake/SFML")
    set(SFML_LIB "${CMAKE_SOURCE_DIR}/dependencies/SFML-IOS/lib/")
    find_package(SFML 2.6 COMPONENTS graphics audio window system network REQUIRED)

    find_library(UIKIT UIKit)
    find_library(FOUNDATION Foundation)
    find_library(OPENGLES OpenGLES)

    message(STATUS "${SFML_INCLUDE_DIR} ${SFML_LIBRARIES} ${UIKIT} ${FOUNDATION} ${OPENGLES} \n ")


    set(LAUNCH_SCREEN "${CMAKE_SOURCE_DIR}/settings/ios/LaunchScreen.storyboard")
    set(ICON_NAME "SAppLogo.icns")
    set(ICON_PATH "${CMAKE_SOURCE_DIR}/settings/ios/${ICON_NAME}")

    add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE ${OBJ_C_FILES} ${SOURCES_FILE} ${ICON_PATH}  ${LAUNCH_SCREEN} ${CMAKE_SOURCE_DIR}/assets)
   
    set_source_files_properties( ${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_source_files_properties( ${LAUNCH_SCREEN} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_source_files_properties("${CMAKE_SOURCE_DIR}/assets" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

    set(RESOURCES ${LAUNCH_SCREEN} "${CMAKE_SOURCE_DIR}/assets")

    set_target_properties(
        ${CMAKE_PROJECT_NAME}
        PROPERTIES
        XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS
        "@executable_path/Frameworks"
    )

    set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")

    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    XCODE_ATTRIBUTE_OTHER_LDFLAGS "-framework UIKit -framework Foundation -framework OpenGLES -lobjc -lc++")
    
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Test command")

    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LIBS} stdc++ -Wall ${UIKIT} ${FOUNDATION} ${OPENGLES} objc)

    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_ICON_FILE ${ICON_NAME}
	    RESOURCE "${RESOURCES}"
        MACOSX_BUNDLE_GUI_IDENTIFIER ${APP_IDENTIFIER}
        MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME}
        XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES YES
        XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET ${DEPLOYMENT_TARGET}
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ${CODE_SIGN_IDENTITY}
        XCODE_ATTRIBUTE_CODE_SIGN_STYLE “Automatic”
        MACOSX_BUNDLE_BUNDLE_VERSION ${APP_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${APP_VERSION}
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/MacOSXBundleInfo.plist.in
    )

    message(NOTICE " Open the ${CMAKE_PROJECT_NAME}.xcodeproj in Xcode to build it. \n")
    
endif()


if (CMAKE_SYSTEM_NAME STREQUAL "Android")

    file(GLOB_RECURSE ANDROID_FILES "src/sys/android/*.cpp")
    project(client)
    include(AndroidNdkModules)
    android_ndk_import_module_cpufeatures()
    set(OPENAL_LIB_PATH ${CMAKE_SOURCE_DIR}/dependencies/SFML/extlibs/libs-android/${ANDROID_ABI}/libopenal.so)
    message("OPENAL_LIB_PATH: ${OPENAL_LIB_PATH} \n")
    add_library(openal SHARED IMPORTED)
    

    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_RELEASE ${OPENAL_LIB_PATH})
    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_DEBUG ${OPENAL_LIB_PATH})
    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_MINSIZEREL ${OPENAL_LIB_PATH})
    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_RELWITHDEBINFO ${OPENAL_LIB_PATH})

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

    message("SOURCE_FILES: ${SOURCES_FILE} \n")

    add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES_FILE} ${ANDROID_FILES})
  
    target_link_libraries(${CMAKE_PROJECT_NAME} 
          -Wl,--whole-archive sfml-main -Wl,--no-whole-archive
          android log GLESv2 EGL ${LIBS} openal)

endif()


