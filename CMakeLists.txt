cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif(APPLE)

project(Bomberman)

include(FetchContent)

FetchContent_Declare(
    graphics
    GIT_REPOSITORY https://github.com/ZimboPro/glfw_test.git
)

FetchContent_GetProperties(graphics)

if(NOT graphics_POPULATED)
    FetchContent_Populate(graphics)
    set(BUILD_SHARED_LIBS TRUE)
    add_subdirectory(${graphics_SOURCE_DIR} ${graphics_BINARY_DIR})
endif()

include_directories(include)

add_executable(
    bomberman
        src/main.cpp
        src/Game.cpp
#        src/SplashScreen.cpp
#        src/MainMenu.cpp
        src/VisibleGameObject.cpp
#        src/Player.cpp
        src/GameObjectManager.cpp
        src/Error.cpp
        src/SFMLSoundProvider.cpp
        src/ServiceLocator.cpp
        src/SoundFileCache.cpp)

target_link_libraries(bomberman graphics) 
