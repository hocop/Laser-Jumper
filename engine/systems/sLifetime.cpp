#include "../gameEngine.hpp"

void GameEngine::sLifetime()
{
    double deltaT = DELTA_T_us * 0.000001;

    // Effects lifetime
    for (auto player : m_entities.getEntities(TAG_PLAYER))
    {
        if (player->cReactor)
        {
            player->cReactor->time -= deltaT;
            if (player->cReactor->time < 0)
                player->cReactor.reset();
        }
    }
}