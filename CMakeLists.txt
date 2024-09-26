cmake_minimum_required(VERSION 3.22.1)
set(APP_NAME "SuperGame")
set(APP_VERSION "0.1.0")
set(APP_IDENTIFIER "com.vsantos1.game")
set(NDK_VERSION "25.1.8937393")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (${APP_NAME} VERSION ${APP_VERSION} LANGUAGES CXX)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "iOS")
    add_subdirectory(dependencies/SFML) # on ios we don't need this, already built SFML-IOS
endif()

file(GLOB_RECURSE SOURCES_FILE game/*.cpp)

set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)


if (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(LIBS sfml-main sfml-graphics sfml-window sfml-system sfml-audio sfml-network sfml-activity)
elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(LIBS sfml-main sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
else()
    set(LIBS sfml-main sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
endif()

set(DIST_DIR ${CMAKE_SOURCE_DIR}/dist)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")

    add_executable(${CMAKE_PROJECT_NAME} ${SOURCES_FILE}  ${CMAKE_SOURCE_DIR}/settings/windows/icon.rc)

    target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

    set(OUTPUT_DIR ${DIST_DIR}/windows/$<CONFIG>)


     add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
         COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${OUTPUT_DIR}
         COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> ${OUTPUT_DIR}
         COMMAND_EXPAND_LISTS
         COMMENT "Building windows distributables"
     )

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_FOLDER} ${OUTPUT_DIR}/assets
        COMMENT "Copying assets to executable directory")

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/dependencies/SFML/extlibs/bin/x64/openal32.dll ${OUTPUT_DIR}
        COMMENT "Copying OpenAL32.dll to executable directory")

   
        
endif() 

if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(SFML_STATIC_LIBRARIES TRUE)

    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum iOS deployment version")

    set(SFML_DIR "${CMAKE_SOURCE_DIR}/dependencies/SFML-IOS/lib/cmake/SFML")
    find_package(SFML 2.6 COMPONENTS graphics audio window system network REQUIRED)

    set(LAUNCH_SCREEN "${CMAKE_SOURCE_DIR}/settings/ios/LaunchScreen.storyboard")
    set(ICON_NAME "SAppLogo.icns")
    set(ICON_PATH "${CMAKE_SOURCE_DIR}/settings/ios/${ICON_NAME}")

    add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE ${SOURCES_FILE} ${ICON_PATH} ${Whereami_SOURCES} ${LAUNCH_SCREEN} ${CMAKE_SOURCE_DIR}/assets)
    set_source_files_properties( ${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_source_files_properties( ${LAUNCH_SCREEN} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_source_files_properties("${CMAKE_SOURCE_DIR}/assets" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

    set(RESOURCES ${LAUNCH_SCREEN} "${CMAKE_SOURCE_DIR}/assets")

    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_ICON_FILE ${ICON_NAME}
	    RESOURCE "${RESOURCES}"
        MACOSX_BUNDLE_GUI_IDENTIFIER ${APP_IDENTIFIER}
        MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME}
        MACOSX_BUNDLE_BUNDLE_VERSION ${APP_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${APP_VERSION}
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/MacOSXBundleInfo.plist.in
    )

    set_property (TARGET ${CMAKE_PROJECT_NAME} PROPERTY XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")

    target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

endif()


if (CMAKE_SYSTEM_NAME STREQUAL "Android")
    project(client)
    include(AndroidNdkModules)
    android_ndk_import_module_cpufeatures()
    set(OPENAL_LIB_PATH ${CMAKE_SOURCE_DIR}/dependencies/SFML/extlibs/libs-android/${ANDROID_ABI}/libopenal.so)
    message("OPENAL_LIB_PATH: ${OPENAL_LIB_PATH}")
    add_library(openal SHARED IMPORTED)
    
    
    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_RELEASE ${OPENAL_LIB_PATH})
    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_DEBUG ${OPENAL_LIB_PATH})
    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_MINSIZEREL ${OPENAL_LIB_PATH})
    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_RELWITHDEBINFO ${OPENAL_LIB_PATH})

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

    message("SOURCE_FILES: ${SOURCES_FILE}")
    add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES_FILE})
  
    target_link_libraries(${CMAKE_PROJECT_NAME} 
          -Wl,--whole-archive sfml-main -Wl,--no-whole-archive
          android log GLESv2 EGL ${LIBS} openal)

endif()


