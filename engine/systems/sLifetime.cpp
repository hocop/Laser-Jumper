#include "../scenes/level.hpp"
#include "../gameEngine.hpp"


void Level::sLifetime()
{
    if (running())
    {
        m_time += m_deltaT;

        // Effects lifetime
        for (auto player : m_entities.getEntities(TAG_PLAYER))
        {
            // Delete reactor
            if (player->cReactor)
            {
                player->cReactor->time -= m_deltaT;
                if (player->cReactor->time < 0)
                    player->cReactor.reset();
            }
            // Update timer
            if (player->cTimer)
                if (player->cTimer->running)
                {
                    player->cTimer->timer += m_deltaT;
                    // Update timer text
                    if (player->cTimer->target)
                        if (player->cTimer->target->cText)
                            player->cTimer->target->cText->setString(player->cTimer->getString());
                }
        }
    }

    if (m_countdown && !m_paused)
    {
        // Count down before start
        m_countdown->cCountdown->time -= m_deltaT;
        // Update countdown text
        m_countdown->cText->setString(m_countdown->cCountdown->getString());
        // Destroy countdown
        if (m_countdown->cCountdown->time <= 0)
        {
            m_countdown->destroy();
            m_countdown.reset();
        }
    }
}