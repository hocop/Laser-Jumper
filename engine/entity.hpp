#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <vector>

#include "components.hpp"


enum EntityTag
{
    TAG_DEFAULT,
    TAG_PLAYER,
    TAG_BLOCK,
    TAG_EFFECT,
    TAG_BUTTON,
    TAG_HUD,
    TAG_CAMERA
};


class Entity
{
    const size_t        m_id;
    const EntityTag     m_tag;
    bool                m_alive;

    Entity(const EntityTag tag, const size_t id) : m_tag(tag), m_id(id), m_alive(true) {};
    friend class EntityManager;

public:
    // Kinematic
    std::shared_ptr<CPosition>      cPosition;
    std::shared_ptr<CVelocity>      cVelocity;
    std::shared_ptr<CCollision>     cCollision;
    std::shared_ptr<CGravity>       cGravity;
    // Shape
    std::shared_ptr<CCircleShape>   cCircleShape;
    std::shared_ptr<CRectShape>     cRectShape;
    std::shared_ptr<CLineShape>     cLineShape;
    // Other
    std::shared_ptr<CEffect>        cEffect;
    // Player
    std::shared_ptr<CControls>      cControls;
    std::shared_ptr<CLaser>         cLaser;
    std::shared_ptr<CReactor>       cReactor;
    std::shared_ptr<CTimer>         cTimer;
    // Graphical
    std::shared_ptr<CSprite>        cSprite;
    std::shared_ptr<CShader>        cShader;
    // Camera
    std::shared_ptr<CCamera>        cCamera;
    // Hud
    std::shared_ptr<CHudTimer>      cHudTimer;


    EntityTag const& tag() {return m_tag;};
    size_t const& id() {return m_id;};
    bool const& alive() {return m_alive;};

    void destroy() {m_alive = false;};

    ~Entity() {};
};
