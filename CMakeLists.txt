cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(Bomberman)

include(FetchContent)

FetchContent_Declare(
    sfml
    URL https://www.sfml-dev.org/files/SFML-2.4.2-sources.zip
)

FetchContent_GetProperties(sfml)

if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    set(BUILD_SHARED_LIBS TRUE)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

include_directories(${sfml_SOURCE_DIR}/include)
include_directories(include)

add_executable(
    bomberman
    src/main.cpp
    src/Game.cpp
        src/SplashScreen.cpp src/MainMenu.cpp)

target_link_libraries(bomberman sfml-graphics sfml-system sfml-window sfml-audio)
