#pragma once

#include "scene.hpp"


class CampaignMenu : public Scene
{
private:

public:
    CampaignMenu(GameEngine& gameEngine);
    ~CampaignMenu() {};

    void sDoAction(const Action& anction);

    void loadCampaign(const std::string& path);
};