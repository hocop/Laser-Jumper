#pragma once

#include "scene.hpp"


class CampaignMenu : public Scene
{
private:

public:
    CampaignMenu(GameEngine& gameEngine);
    ~CampaignMenu() {};

    void update();
    void sDoAction(const Action& anction);
    // void sRender();
    void reset() {};
};