#include "../scenes/level.hpp"


void Level::sDoAction(const Action& action)
{
    if (action.name() == "exit" && action.type() == "start")
        m_gameEngine->quit();
    
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


Vec2 Level::screenToWorld(const Vec2& pos)
{
    auto winSz = m_gameEngine->window().getSize();
    sf::Vector2f screenPos(pos.x / float(winSz.x) * 2 - 1, 1 - pos.y / float(winSz.y) * 2);
    const sf::Transform& tr = m_camera->cCamera->view.getInverseTransform();
    return tr.transformPoint(screenPos);
}

Vec2 Level::worldToScreen(const Vec2& pos)
{
    auto winSz = m_gameEngine->window().getSize();
    const sf::Transform& tr = m_camera->cCamera->view.getTransform();
    sf::Vector2f screenPos = tr.transformPoint(pos.as_sf());
    return Vec2(
        (screenPos.x + 1) * float(winSz.x) * 0.5,
        (1 + screenPos.y) * float(winSz.y) * 0.5
    );
}
