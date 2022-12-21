#include "campaignMenu.hpp"
#include "../gameEngine.hpp"


CampaignMenu::CampaignMenu(GameEngine& gameEngine)
{
    // Store pointer to gameEngine
    m_gameEngine = &gameEngine;

    // Register actions
    registerAction(sf::Keyboard::Q,         "exit");
    registerAction(sf::Keyboard::Space,     "play_hard");

    // Add buttons
    spawnButtonRect("01 - Hard",            "play_hard",    Vec2(0.1, 0.2),    Vec2(0.4, 0.1));
    spawnButtonRect("02 - Deadly",          "play_deadly",  Vec2(0.1, 0.4),    Vec2(0.4, 0.1));
    spawnButtonRect("Exit",                 "exit",         Vec2(0.1, 0.6),    Vec2(0.4, 0.1));
}


void CampaignMenu::sDoAction(const Action& action)
{
    if (action.name() == "exit" && action.type() == "start")
        m_gameEngine->changeScene("main_menu");

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
