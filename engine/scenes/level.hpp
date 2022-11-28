#pragma once

#include "scene.hpp"
#include "../gameEngine.hpp"

const double CONTACT_EPS = 0.001;


class Level : public Scene
{
private:
    double                  m_deltaT;
    float                   m_time;
    bool                    m_paused = false;

    std::shared_ptr<Entity> m_camera;
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_timer;

public:
    Level(GameEngine& gameEngine);
    ~Level() {};

    void update();
    void sDoAction(const Action& anction);
    void sRender();

    std::shared_ptr<Entity> spawnPlayer(const Vec2& pos);
    void                    spawnCamera(const CameraType& focus);
    void                    spawnHud();
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

void resetGeometryPosition(std::shared_ptr<Entity> &entity);