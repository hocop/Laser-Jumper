#include "mainMenu.hpp"
#include "../gameEngine.hpp"


MainMenu::MainMenu(GameEngine& gameEngine)
{
    // Store pointer to gameEngine
    m_gameEngine = &gameEngine;

    // Register actions
    registerAction(sf::Keyboard::Q,         "exit");
    registerAction(sf::Keyboard::Space,     "play_hard");

    // Add buttons
    spawnButtonRect("Play hard level",      "play_hard",    Vec2(0.1, 0.2),    Vec2(0.4, 0.1));
    spawnButtonRect("Play deadly level",    "play_deadly",  Vec2(0.1, 0.4),    Vec2(0.4, 0.1));
    spawnButtonRect("Exit",                 "exit",         Vec2(0.1, 0.6),    Vec2(0.4, 0.1));
}


void MainMenu::update()
{
    // Add and delete entities
    m_entities.update();
}


void MainMenu::sDoAction(const Action& action)
{
    if (action.name() == "exit" && action.type() == "start")
        m_gameEngine->quit();

    if (action.name() == "play_hard" && action.type() == "start")
    {
        m_gameEngine->changeScene("hard");
        m_gameEngine->currentScene()->reset();
    }

    if (action.name() == "play_deadly" && action.type() == "start")
    {
        m_gameEngine->changeScene("deadly");
        m_gameEngine->currentScene()->reset();
    }
}
