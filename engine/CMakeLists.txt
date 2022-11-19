add_library(
    engine
    entity.cpp
    entityManager.cpp
    vec2.cpp
    gameEngine.cpp
    systems/sCollision.cpp
    systems/sPhysics.cpp
    systems/sRender.cpp
    systems/sUserInput.cpp
)

target_link_libraries(engine PRIVATE sfml-graphics)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/extensions/SFML")