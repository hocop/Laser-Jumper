#include "campaignMenu.hpp"
#include "../gameEngine.hpp"
#include "../utils/reading.hpp"


std::string getDisplayName(int i)
{
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << i;
    std::string displayName = ss.str();
    return displayName;
}


CampaignMenu::CampaignMenu(GameEngine& gameEngine)
{
    // Store pointer to gameEngine
    m_gameEngine = &gameEngine;

    // Register actions
    registerAction(sf::Keyboard::Q,         "exit");
    registerAction(sf::Keyboard::Escape,    "exit");
    registerAction(sf::Keyboard::BackSpace, "exit");
    registerAction(sf::Keyboard::Space,     "play_selected");
    registerAction(sf::Keyboard::Enter,     "play_selected");
    registerAction(sf::Keyboard::Up,        "select_prev");
    registerAction(sf::Keyboard::Down,      "select_next");

    // Add buttons
    spawnButtonRect("X", "exit",    Vec2(.9, .001),    Vec2(.1, .1));

    // Map info section
    m_lbMapName = spawnText("Map Name",   Vec2(0.75, 0.2));
}


void CampaignMenu::load(const std::string& path)
{
    m_path = path;
    std::string mainFilePath = rd::join(path, "campaign.json");
    
    std::ifstream f(mainFilePath);
    std::cout << "Reading " << mainFilePath << std::endl;
    json campaign = json::parse(f);

    // Get map name
    // m_mapName = map["name"];

    // Load items
    for (auto item : campaign["maps"])
    {
        std::string s(item);
        m_maps.push_back(s);
    }

    // Add map buttons
    for (int i = 0; i < m_maps.size(); i++)
    {
        std::string displayName = getDisplayName(i + 1);
        double xCoord = (i / 5) / 5.0 * 0.6 + 0.05;
        double yCoord = (i % 5) / 5.0 * 0.5 + 0.25;
        auto button = spawnButtonRect(displayName, "play_" + displayName, Vec2(xCoord, yCoord), Vec2(0.1, 0.07));
        m_mapButtons.push_back(button);
    }
}

void CampaignMenu::update()
{
    // Add and delete entities
    m_entities.update();
    
    // Highlight selected button
    for (int i = 0; i < m_mapButtons.size(); i++)
    {
        if (i == m_selectedMap)
            m_mapButtons[i]->cRectShape->rect.setOutlineThickness(2);
        else
            m_mapButtons[i]->cRectShape->rect.setOutlineThickness(0);
    }

    // Write map name
    std::string mapPath = rd::join(m_path, m_maps[m_selectedMap], "map.json");
    json mapHeader = rd::read_json(mapPath);

    m_lbMapName->cText->setString(mapHeader["name"]);
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int pythonmod(int i, int m)
{
    if (i < 0)
        i += ((-i) / m + 1) * m;
    return i % m;
}

void CampaignMenu::sDoAction(const Action& action)
{
    if (action.name() == "exit" && action.type() == "start")
        m_gameEngine->changeScene("main_menu");

    if (action.name() == "play_selected" && action.type() == "start")
        loadLevel(m_selectedMap);

    if (action.name() == "select_next" && action.type() == "start")
        m_selectedMap = pythonmod(m_selectedMap + 1, m_maps.size());

    if (action.name() == "select_prev" && action.type() == "start")
        m_selectedMap = pythonmod(m_selectedMap - 1, m_maps.size());

    if (action.name().find("play_") == 0 && action.name().size() == 7 && action.type() == "start")
    {
        std::string num = action.name().substr(5, 2);
        if (is_number(num))
            loadLevel(std::stoi(num) - 1);
    }
}

void CampaignMenu::loadLevel(int mapId)
{
    std::string mapPath = rd::join(m_path, m_maps[mapId]);
    Level level(*m_gameEngine);
    m_gameEngine->addScene("level", std::make_shared<Level>(level));
    m_gameEngine->changeScene("level");
    m_gameEngine->currentScene()->load(mapPath);
    m_gameEngine->currentScene()->reset();
}