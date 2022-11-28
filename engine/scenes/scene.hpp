#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <unordered_map>

#include "../../extensions/nlohmann/json.hpp"
using json = nlohmann::json;

#include "../entity/entityManager.hpp"
#include "../utils/vec2.hpp"
#include "../utils/assets.hpp"
#include "../utils/action.hpp"
#include "../utils/keycodes.hpp"


class GameEngine;


typedef std::unordered_map<int, std::string> ActionMap;


class Scene
{
protected:
    EntityManager   m_entities;
    GameEngine*     m_gameEngine;
    ActionMap       m_actionMap;

public:
    Scene() {};
    Scene(GameEngine& gameEngine);
    ~Scene() {};

    virtual void update() = 0;
    virtual void sDoAction(const Action& action) = 0;
    virtual void sRender() = 0;

    void registerAction(const int& key, const std::string& actionName)
    {
        m_actionMap[key] = actionName;
    };

    ActionMap& actionMap() {return m_actionMap;};
    const EntityVec& getHud() {return m_entities.getEntities(TAG_HUD);};

    void spawnButtonRect(const std::string& action, const std::string& text, const Vec2& pos, const Vec2& size);
};


void drawEntity(sf::RenderWindow& window, const std::shared_ptr<Entity> &entity);
void drawHud(sf::RenderWindow& window, const std::shared_ptr<Entity> &entity);