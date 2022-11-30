#include "../gameEngine.hpp"
#include "../scenes/level.hpp"


std::shared_ptr<Entity> Level::spawnTimer()
{
    if (m_timer)
        m_timer->destroy();

    Vec2 ws = m_gameEngine->window().getSize();

    m_timer = m_entities.addEntity(TAG_HUD);
    m_timer->cPosition = std::make_shared<CPosition>(Vec2(ws.x * 0.5, ws.y * 0.95));
    m_timer->cText = std::make_shared<CText>(m_gameEngine->assets().getFont("regular"));
    m_timer->cText->text.setString("0.00");

    auto textBox = m_timer->cText->text.getGlobalBounds();
    m_timer->cText->text.setOrigin(sf::Vector2f(textBox.width / 2.0, textBox.height / 2.0));

    resetGeometryPosition(m_timer);

    return m_timer;
}


std::shared_ptr<Entity> Level::spawnCountdown()
{
    if (m_countdown)
        m_countdown->destroy();
    
    Vec2 ws = m_gameEngine->window().getSize();

    m_countdown = m_entities.addEntity(TAG_HUD);
    m_countdown->cCountdown = std::make_shared<CCountdown>();
    m_countdown->cPosition = std::make_shared<CPosition>(Vec2(ws.x * 0.5, ws.y * 0.3));
    m_countdown->cText = std::make_shared<CText>(m_gameEngine->assets().getFont("regular"));
    m_countdown->cText->text.setCharacterSize(48);
    m_countdown->cText->setString("3");

    resetGeometryPosition(m_countdown);

    return m_countdown;
}