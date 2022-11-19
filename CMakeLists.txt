cmake_minimum_required(VERSION 3.24.2)

project(LaserJumper)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Save to json" FORCE)

add_executable(${PROJECT_NAME} main.cpp)

# Build SFML
add_subdirectory(extensions/SFML-2.5.1)
target_link_libraries(${PROJECT_NAME} sfml-graphics)

# Build engine
add_subdirectory(engine)
target_link_libraries(${PROJECT_NAME} engine)