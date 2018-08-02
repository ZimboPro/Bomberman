cmake_minimum_required(3.11 FATAL_ERROR)

project(Bomberman)

include(FetchContent)

FetchContent_Declare(
    engine
    URL https://github.com/ZimboPro/GameEngine.git
)

FetchContent_GetProperties(engine)

if(NOT engine_POPULATED)
    FetchContent_Populate(engine)
    add_subdirectory(${engine_SOURCE_DIR} ${engine_BINARY_DIR})
endif()

include_directories(${engine_SOURCE_DIR}/include)
include_directories(include)

add_executable(
    bomberman
    src/main.hpp
)

target_link_libraries(bomberman GameEngine)