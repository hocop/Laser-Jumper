#include "../scenes/level.hpp"
#include "../gameEngine.hpp"


void Level::sLifetime()
{
    if (!m_paused)
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
                            player->cTimer->target->cText->text.setString(std::to_string(player->cTimer->timer));
                }
        }
    }
}