#include "mainMenu.hpp"
#include "../gameEngine.hpp"


MainMenu::MainMenu(GameEngine& gameEngine)
{
    // Store pointer to gameEngine
    m_gameEngine = &gameEngine;

    // Register actions
    registerAction(sf::Keyboard::Q,         "exit");
    registerAction(sf::Keyboard::Escape,    "exit");
    registerAction(sf::Keyboard::Space,     "play");
    registerAction(sf::Keyboard::Enter,     "play");

    // Add text
    spawnText("Hello, " + m_gameEngine->playerName(),   Vec2(0.2, 0.2),     ALIGN_CENTER, ALIGN_CENTER);

    // Add buttons
    spawnButtonRect("Choose level",         "play",     Vec2(0.1, 0.4),    Vec2(0.4, 0.1));
    spawnButtonRect("Exit",                 "exit",     Vec2(0.1, 0.6),    Vec2(0.4, 0.1));
}


void MainMenu::sDoAction(const Action& action)
{
    if (action.name() == "exit" && action.type() == "start")
        m_gameEngine->quit();

    if (action.name() == "play" && action.type() == "start")
    {
        m_gameEngine->changeScene("campaign_menu");
        m_gameEngine->currentScene()->reset();
    }
}
