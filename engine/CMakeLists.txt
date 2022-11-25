add_library(
    engine
    entity/entityManager.cpp
    utils/assets.cpp
    utils/vec2.cpp
    utils/keycodes.cpp
    gameEngine.cpp
    systems/sCollision.cpp
    systems/sPhysics.cpp
    systems/sRender.cpp
    systems/sUserInput.cpp
    systems/sLifetime.cpp
    systems/factory.cpp
)

target_link_libraries(engine PRIVATE sfml-graphics)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/extensions/SFML")