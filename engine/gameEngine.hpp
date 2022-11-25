#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <unordered_map>

#include "../extensions/nlohmann/json.hpp"
using json = nlohmann::json;

#include "entity/entityManager.hpp"
#include "utils/vec2.hpp"
#include "utils/assets.hpp"
#include "utils/action.hpp"
#include "utils/keycodes.hpp"

const long int DELTA_T_us = 10000;
const double CONTACT_EPS = 0.001;
const int STEPS_PER_FRAME = 2;

class GameEngine
{
    sf::RenderWindow        m_window;
    bool                    m_running = true;
    bool                    m_paused = false;
    Assets                  m_assets;

    // TODO: move to scene:
    double                  m_deltaT;
    float                   m_time;
    std::shared_ptr<Entity> m_camera;
    EntityManager           m_entities;
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_timer;
    std::unordered_map<int, std::string> m_actionMap;



public:

    GameEngine();
    ~GameEngine();

    void run();

    void sUserInput();

    // TODO: move to scene:
    std::shared_ptr<Entity> spawnPlayer(const Vec2& pos);
    void                    spawnCamera(const CameraType& focus);
    void                    spawnHud();
    std::shared_ptr<Entity> spawnRect(const Vec2& pos, double width, double height, float angle=0);
    std::shared_ptr<Entity> spawnLine(const Vec2& pos, double length, float angle=0, bool doubleSided=true);
    std::shared_ptr<Entity> spawnEffect(const Vec2& pos, const EffectType& type, const double& angle=0);

    void sCollision();
    void sPhysics();
    void sRender();
    void sLifetime();
    void sDoAction(const Action& anction);
    void loadMap(const std::string& path);

    void processCollisions(std::shared_ptr<Entity>& player, std::shared_ptr<Entity>& entity);
    void registerAction(const int& key, const std::string& actionName);
    void applyEffect(std::shared_ptr<Entity>& effect, std::shared_ptr<Entity>& player);
    void setShaderParams(std::shared_ptr<Entity>& entity);

    Vec2 screenToWorld(const Vec2& pos);
    Vec2 worldToScreen(const Vec2& pos);
};


void resetGeometryPosition(std::shared_ptr<Entity> &entity);
void drawEntity(sf::RenderWindow& window, const std::shared_ptr<Entity> &entity);
void drawHud(sf::RenderWindow& window, const std::shared_ptr<Entity> &entity);