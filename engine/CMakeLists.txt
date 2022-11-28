add_library(
    engine
    
    entity/entityManager.cpp

    gameEngine.cpp

    scenes/level.cpp

    utils/assets.cpp
    utils/vec2.cpp
    utils/keycodes.cpp

    systems/factory.cpp
    systems/sCollision.cpp
    systems/sDoAction.cpp
    systems/sLifetime.cpp
    systems/sPhysics.cpp
    systems/sRender.cpp
    systems/sUserInput.cpp
)

target_link_libraries(engine PRIVATE sfml-graphics)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/extensions/SFML")