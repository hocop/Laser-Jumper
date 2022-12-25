#pragma once
#include <sstream>
#include <iomanip>

#include "scene.hpp"
#include "level.hpp"


class CampaignMenu : public Scene
{
private:
    std::vector<std::string>    m_maps;
    EntityVec                   m_mapButtons;
    std::string                 m_path;
    void                        loadLevel(int mapId);
    int                         m_selectedMap=0;

    std::shared_ptr<Entity>     m_lbMapName;
    EntityVec                   m_lbPlayerNames;
    EntityVec                   m_lbTimes;

public:
    CampaignMenu(GameEngine& gameEngine);
    ~CampaignMenu() {};

    void load(const std::string& path) override;
    void sDoAction(const Action& anction);
    void update() override;

    void loadCampaign(const std::string& path);
};