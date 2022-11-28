#include "mainMenu.hpp"
#include "../gameEngine.hpp"


MainMenu::MainMenu(GameEngine& gameEngine)
{
    // Store pointer to gameEngine
    m_gameEngine = &gameEngine;

    // Register actions
    registerAction(sf::Keyboard::Q,         "exit");

    // Add buttons
    spawnButtonRect("Play hard level",      "play_hard",    Vec2(200, 200),    Vec2(300, 50));
    spawnButtonRect("Play deadly level",    "play_deadly",  Vec2(200, 300),    Vec2(300, 50));
    spawnButtonRect("Exit",                 "exit",         Vec2(200, 400),    Vec2(300, 50));
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
