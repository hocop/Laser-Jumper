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

# Copy resources
# add_custom_command(TARGET RoE POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${PROJECT_SOURCE_DIR}/resource
#     ${PROJECT_BINARY_DIR}/resource
#     COMMENT "Copying resources into binary directory")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resource
    ${PROJECT_BINARY_DIR}/resource
    COMMENT "Copying resources into binary directory"
)