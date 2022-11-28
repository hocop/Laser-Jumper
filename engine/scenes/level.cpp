#include "level.hpp"


Level::Level()
{
    // Init constants
    m_deltaT = DELTA_T_us * 0.000001;

    // Register actions TODO: move to scene class
    registerAction(sf::Keyboard::Space,     "jump");
    registerAction(sf::Keyboard::Enter,     "restart");
    registerAction(sf::Keyboard::P,         "pause");
    registerAction(sf::Keyboard::Q,         "exit");
    registerAction(sf::Keyboard::Y,         "deleteLast");
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