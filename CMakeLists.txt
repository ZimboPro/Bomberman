cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif(APPLE)

# unzip folder
set(UNZIP FALSE)
if (${UNZIP})
    execute_process(
        COMMAND unzip package.zip -d ${CMAKE_BINARY_DIR}/assets
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(
    bomberman
        src/main.cpp
        src/Game.cpp
        src/SplashScreen.cpp
        src/Menus/MainMenu.cpp
        src/game_elements/Block.cpp
        src/game_elements/Grass.cpp
        src/game_elements/VisibleGameObject.cpp
        src/game_elements/Player.cpp
        src/GameObjectManager.cpp
        src/Error.cpp
        src/sound/SFMLSoundProvider.cpp
        src/ServiceLocator.cpp
        src/sound/SoundFileCache.cpp
        src/Map.cpp
        src/ObjectFactory.cpp
        src/Menus/OptionsMenu.cpp
        src/LoadingScreen.cpp
        src/GameInterface.cpp
        src/game_elements/Goomba.cpp
        src/game_elements/KoopaTroopa.cpp
        src/game_elements/powerBlock.cpp
        src/game_elements/HealthBlock.cpp
        src/map_generation/Levels.cpp
        src/map_generation/Save.cpp
        src/map_generation/MapError.cpp
        src/game_elements/Bomb.cpp
        src/Menus/KeyBindMenu.cpp
        src/Menus/StartGameMenu.cpp
        src/Menus/PauseMenu.cpp
        src/game_elements/Fire.cpp include/game_elements/Fire.hpp
        src/Menus/LevelSelectMenu.cpp
        src/Screens/LevelPassed.cpp
        src/Screens/GameOver.cpp
        src/Screens/GameWon.cpp
		src/game_elements/Pipe.cpp

        )

add_dependencies(bomberman graphics)
find_package(Boost REQUIRED COMPONENTS system serialization)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(bomberman graphics ${Boost_LIBRARIES}) 
