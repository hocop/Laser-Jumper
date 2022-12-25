#include "level.hpp"
#include "../gameEngine.hpp"
#include "../utils/reading.hpp"


Level::Level(GameEngine& gameEngine)
{
    // Store pointer to gameEngine
    m_gameEngine = &gameEngine;

    // Init constants
    m_deltaT = DELTA_T_us * 0.000001;

    // Register actions
    registerAction(sf::Keyboard::Space,     "jump");
    registerAction(sf::Keyboard::Enter,     "restart");
    registerAction(sf::Keyboard::P,         "pause");
    registerAction(sf::Keyboard::Q,         "exit");
    registerAction(sf::Keyboard::Escape,    "exit");
    registerAction(sf::Keyboard::BackSpace, "exit");
    registerAction(sf::Keyboard::Y,         "delete_last");
    registerAction(sf::Keyboard::C,         "change_level");

    // Add buttons
    spawnButtonRect("X", "exit",    Vec2(.9, .001),    Vec2(.1, .1));
    spawnButtonRect("R", "restart", Vec2(.0, .001),     Vec2(.1, .1));
}


void Level::update()
{
    // Add and delete entities
    m_entities.update();
    
    // Detect and process all collisions
    sCollision();

    // Physics step
    sPhysics();

    // Process temporary things such as effects
    sLifetime();
}


void Level::load(const std::string& path)
{
    std::string mainFilePath = rd::join(path, "map.json");
    
    std::ifstream f(mainFilePath);
    std::cout << "Reading " << mainFilePath << std::endl;
    json map = json::parse(f);

    // Get map name
    m_mapName = map["name"];

    // Load items
    for (auto item : map["items"])
    {
        if (item["type"] == "reactor")
            spawnEffect(Vec2(item["x"], item["y"]), EFFECT_REACTOR, rd::get<double>(item, "angle", 0.0));

        else if (item["type"] == "finish")
            spawnEffect(Vec2(item["x"], item["y"]), EFFECT_FINISH, rd::get<double>(item, "angle", 0.0));

        else if (item["type"] == "landscape")
            loadLandscape(rd::join(path, item["file"]));
    }
}


void Level::reset()
{
    // Remove all players
    EntityVec& players = m_entities.getEntities(TAG_PLAYER);
    for (int i = 0; i < players.size(); i++)
        players[i]->destroy();

    // Start new run
    spawnCamera(CAMERA_FOCUS_PLAYER);
    spawnTimer();
    spawnPlayer(Vec2(0, 1));
    spawnCountdown();
}


void Level::sDoAction(const Action& action)
{
    if (action.name() == "exit" && action.type() == "start")
        m_gameEngine->changeScene("campaign_menu");
    
    if (action.name() == "pause" && action.type() == "start")
        m_paused = !m_paused;
    
    if (action.name() == "change_level" && action.type() == "start")
    {
        if (m_gameEngine->currentSceneName() == "hard")
            m_gameEngine->changeScene("deadly");
        else
            m_gameEngine->changeScene("hard");
    }

    if (action.name() == "restart" && action.type() == "start")
    {
        reset();
    }

    if (action.name() == "delete_last" && action.type() == "start")
    {
        EntityVec& players = m_entities.getEntities(TAG_PLAYER);
        if(players.size() > 0)
            players[players.size() - 1]->destroy();
    }

    if (action.name() == "jump" && running())
        if(m_player)
            if (action.type() == "start" && m_player->cControl)
                m_player->cLaser->lengthTgt = m_player->cLaser->lengthActive;
            else
                m_player->cLaser->lengthTgt = m_player->cLaser->lengthNeutral;
}


bool Level::running()
{
    return !m_paused && !m_countdown;
};


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
