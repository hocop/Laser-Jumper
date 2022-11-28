#include "level.hpp"


Level::Level(GameEngine& gameEngine)
{
    // Store pointer to gameEngine
    m_gameEngine = &gameEngine;

    // Init constants
    m_deltaT = DELTA_T_us * 0.000001;

    // Register actions TODO: move to scene class
    registerAction(sf::Keyboard::Space,     "jump");
    registerAction(sf::Keyboard::Enter,     "restart");
    registerAction(sf::Keyboard::P,         "pause");
    registerAction(sf::Keyboard::Q,         "exit");
    registerAction(sf::Keyboard::Y,         "delete_last");
    registerAction(sf::Keyboard::C,         "change_level");

    // Add buttons
    spawnButtonRect("exit",     "X", Vec2(1200, 25),    Vec2(80, 50));
    spawnButtonRect("restart",  "R", Vec2(500, 25),     Vec2(80, 50));

    // Add timer
    m_timer = m_entities.addEntity(TAG_HUD);
    m_timer->cText = std::make_shared<CText>(m_gameEngine->assets().getFont("regular"));
}


void Level::update()
{
    // Add and delete entities
    m_entities.update();
    
    // Detect and process all collisions
    sCollision();

    // Physics step
    sPhysics();

    // Process temporary things such as effects
    sLifetime();
}