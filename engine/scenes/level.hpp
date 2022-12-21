#pragma once

#include "scene.hpp"

const double CONTACT_EPS = 0.001;


class Level : public Scene
{
private:
    double                  m_deltaT;
    float                   m_time;
    bool                    m_paused = false;
    std::string             m_mapName;

    std::shared_ptr<Entity> m_camera;
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_timer;
    std::shared_ptr<Entity> m_countdown;

    void loadLandscape(const std::string& path);

public:
    Level(GameEngine& gameEngine);
    ~Level() {};

    void sDoAction(const Action& anction);

    void update() override;
    void reset() override;
    void sRender() override;

    bool running();

    std::shared_ptr<Entity> spawnPlayer(const Vec2& pos);
    std::shared_ptr<Entity> spawnCamera(const CameraType& focus);
    std::shared_ptr<Entity> spawnTimer();
    std::shared_ptr<Entity> spawnCountdown();
    std::shared_ptr<Entity> spawnRect(const Vec2& pos, double width, double height, float angle=0);
    std::shared_ptr<Entity> spawnLine(const Vec2& pos, double length, float angle=0, bool doubleSided=true);
    std::shared_ptr<Entity> spawnEffect(const Vec2& pos, const EffectType& type, const double& angle=0);

    void sCollision();
    void sPhysics();
    void sLifetime();
    void loadMap(const std::string& path);

    void processCollisions(std::shared_ptr<Entity>& player, std::shared_ptr<Entity>& entity);
    void applyEffect(std::shared_ptr<Entity>& effect, std::shared_ptr<Entity>& player);
    void setShaderParams(std::shared_ptr<Entity>& entity);

    Vec2 screenToWorld(const Vec2& pos);
    Vec2 worldToScreen(const Vec2& pos);
};