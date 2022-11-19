#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <chrono>
#include <unistd.h>
#include <fstream>

#include "../extensions/nlohmann/json.hpp"
using json = nlohmann::json;

#include "entityManager.hpp"
#include "vec2.hpp"

const int DELTA_T_us = 10000;
const double CONTACT_EPS = 0.001;

class GameEngine
{
    EntityManager       m_entities;
    sf::RenderWindow    m_window;
    sf::Color           m_bgColor;
    bool                m_running = true;

    sf::Texture         m_laserTexture;
    sf::Texture         m_contactTexture;

public:

    GameEngine();
    ~GameEngine();

    void run();

    std::shared_ptr<Entity> spawnPlayer(const Vec2& pos);
    std::shared_ptr<Entity> spawnCamera(const CameraType& focus);
    std::shared_ptr<Entity> spawnRect(const Vec2& pos, double width, double height, float angle=0);
    std::shared_ptr<Entity> spawnLine(const Vec2& pos, double length, float angle=0, bool doubleSided=true);
    std::shared_ptr<Entity> spawnEffect();

    void sUserInput();
    void sCollision();
    void sPhysics();
    void sRender();

    void loadMap(const std::string& path);
};


void resetGeometryPosition(std::shared_ptr<Entity> &entity);
void drawEntity(sf::RenderWindow& window, const std::shared_ptr<Entity> &entity);