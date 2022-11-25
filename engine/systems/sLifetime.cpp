#include "../gameEngine.hpp"

void GameEngine::sLifetime()
{
    if (!m_paused)
    {
        m_time += m_deltaT;

        // Effects lifetime
        for (auto player : m_entities.getEntities(TAG_PLAYER))
        {
            if (player->cReactor)
            {
                player->cReactor->time -= m_deltaT;
                if (player->cReactor->time < 0)
                    player->cReactor.reset();
            }
            if (player->cTimer)
                if (player->cTimer->running)
                    player->cTimer->timer += m_deltaT;
        }
    }
}