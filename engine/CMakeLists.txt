add_library(
    engine
    
    entity/entityManager.cpp

    gameEngine.cpp

    scenes/level.cpp
    scenes/mainMenu.cpp
    scenes/campaignMenu.cpp

    utils/assets.cpp
    utils/keycodes.cpp
    utils/reading.cpp
    utils/vec2.cpp

    factory/moving.cpp
    factory/stationary.cpp
    factory/buttons.cpp
    factory/hud.cpp

    systems/sCollision.cpp
    systems/sLifetime.cpp
    systems/sPhysics.cpp
    systems/sRender.cpp
    systems/sUserInput.cpp
)

target_link_libraries(engine PRIVATE sfml-graphics)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/extensions/SFML")