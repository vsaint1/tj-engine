cmake_minimum_required(VERSION 3.22.1)
project(client)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(dependencies/SFML)
add_subdirectory(dependencies/glm)

file(GLOB_RECURSE SOURCES_FILE game/*.cpp)

set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)


if (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(LIBS sfml-main sfml-graphics sfml-window sfml-system sfml-audio sfml-network sfml-activity glm)
else()
    set(LIBS sfml-main sfml-graphics sfml-window sfml-system sfml-audio sfml-network glm)
endif()

set(DIST_DIR ${CMAKE_SOURCE_DIR}/dist)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")

    add_executable(${CMAKE_PROJECT_NAME} ${SOURCES_FILE})
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

if (CMAKE_SYSTEM_NAME STREQUAL "Android")

    include(AndroidNdkModules)
    android_ndk_import_module_cpufeatures()
    set(OPENAL_LIB_PATH ${CMAKE_SOURCE_DIR}/dependencies/SFML/extlibs/libs-android/${ANDROID_ABI}/libopenal.so)
    message("OPENAL_LIB_PATH: ${OPENAL_LIB_PATH}")
    add_library(openal SHARED IMPORTED)
    
    
    set_target_properties(openal PROPERTIES  IMPORTED_LOCATION_RELEASE ${OPENAL_LIB_PATH} IMPORTED_LOCATION_DEBUG ${OPENAL_LIB_PATH})

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

    message("SOURCE_FILES: ${SOURCES_FILE}")
    add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES_FILE})
  
    target_link_libraries(${CMAKE_PROJECT_NAME} 
          -Wl,--whole-archive sfml-main -Wl,--no-whole-archive
          android log GLESv1_CM EGL ${LIBS} openal)

endif()


