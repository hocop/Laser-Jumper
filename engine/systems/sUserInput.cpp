#include "../gameEngine.hpp"


void GameEngine::sUserInput()
{
    // Event handling
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Window closed
        if (event.type == sf::Event::Closed)
            m_running = false;

        // Mouse button pressed
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Get click position and spawn player
                Vec2 clickPos = screenToWorld(Vec2(event.mouseButton.x, event.mouseButton.y));
                spawnPlayer(clickPos);
            }
        }

        // Key pressed
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            // Find this key in the keymap
            if (m_actionMap.find(event.key.code) != m_actionMap.end())
            {
                // Determine action type
                const std::string type = (event.type == sf::Event::KeyPressed) ? "start" : "end";

                // Send action to the scene
                sDoAction(Action(m_actionMap[event.key.code], type));
            }
        }
    }
}


void GameEngine::registerAction(const int& key, const std::string& actionName)
{
    m_actionMap[key] = actionName;
}


void GameEngine::sDoAction(const Action& action)
{
    if (action.name() == "exit" && action.type() == "start")
        m_running = false;
    
    if (action.name() == "pause" && action.type() == "start")
        m_paused = !m_paused;
    
    if (action.name() == "restart" && action.type() == "start")
    {
        EntityVec& players = m_entities.getEntities(TAG_PLAYER);
        if(players.size() > 0)
            players[players.size() - 1]->destroy();
        spawnPlayer(Vec2(0, -1));
    }

    if (action.name() == "deleteLast" && action.type() == "start")
    {
        EntityVec& players = m_entities.getEntities(TAG_PLAYER);
        if(players.size() > 0)
            players[players.size() - 1]->destroy();
    }

    if (action.name() == "jump")
        if(m_player)
            if (action.type() == "start")
                m_player->cLaser->lengthTgt = m_player->cLaser->lengthActive;
            else
                m_player->cLaser->lengthTgt = m_player->cLaser->lengthNeutral;
}


Vec2 GameEngine::screenToWorld(const Vec2& pos)
{
    auto winSz = m_window.getSize();
    sf::Vector2f screenPos(pos.x / float(winSz.x) * 2 - 1, 1 - pos.y / float(winSz.y) * 2);
    const sf::Transform& tr = m_camera->cCamera->view.getInverseTransform();
    return tr.transformPoint(screenPos);
}

Vec2 GameEngine::worldToScreen(const Vec2& pos)
{
    auto winSz = m_window.getSize();
    const sf::Transform& tr = m_camera->cCamera->view.getTransform();
    sf::Vector2f screenPos = tr.transformPoint(pos.as_sf());
    return Vec2(
        (screenPos.x + 1) * float(winSz.x) * 0.5,
        (1 + screenPos.y) * float(winSz.y) * 0.5
    );
}
