#pragma once

#include "vec2.hpp"
#include <SFML/Graphics.hpp>
#include "../extensions/nlohmann/json.hpp"
using json = nlohmann::json;


enum ControlType
{
    CONTROL_FULL,
    CONTROL_SPLIT_L,
    CONTROL_SPLIT_R
};

enum EffectType
{
    EFFECT_REACTOR_R,
    EFFECT_REACTOR_L,
    EFFECT_FLIP,
    EFFECT_RESET,
    EFFECT_NOLASER,
    EFFECT_NOBACKWARDS
};

enum CameraType
{
    CAMERA_FOCUS_PLAYER,
    CAMERA_FREE
};

class CPosition
{
    public:
    Vec2 vec;
    CPosition() {};
    CPosition(const Vec2& vecIn) : vec(vecIn) {};
};

class CVelocity
{
    public:
    Vec2 vec;
    CVelocity() {};
    CVelocity(const Vec2& vecIn) : vec(vecIn) {};
};

class CCollision
{
public:
    double  bounciness;
    bool    physical;
    CCollision(const double& dampingIn=1.0, const bool& physical=true)
    :   bounciness(dampingIn), physical(physical)
    {};
};


class CReactor
{
public:
    Vec2    force;
    double  time;
    sf::Sprite sprite;

    CReactor(const Vec2& force, const double& time, const sf::Texture& texture)
    : force(force), time(time)
    {
        sprite.setTexture(texture);
        auto texSize = texture.getSize();
        sprite.setOrigin(sf::Vector2f(texSize.x, texSize.y / 2.0));
        sprite.setScale(sf::Vector2f(0.5 / texSize.x, 0.5 / texSize.y));
    };
};


class CGravity
{
    public:
    double g = 9.8;
};

class CControls
{
    public:
    ControlType type = CONTROL_FULL;

    CControls() {};
    ~CControls() {};
};

class CReplay
{
public:
    std::vector<bool> replay;

    CReplay(const std::string& path) {
        // std::ifstream f(path);
        // json r = json::parse(f);
        // int i = 0;
        // int pressed = false;
        // for(auto event : r["events"])
        // {
        //     while (i < event["t"])
        //     {
        //         replay.push_back(pressed);
        //         i++;
        //     }
        //     pressed = event["pressed"];
        // }
    };
    ~CReplay() {};
};


class CEffect
{
public:
    EffectType type;
    sf::Sprite sprite;

    CEffect(double width, double height, const EffectType& type, const sf::Texture& texture)
    :   type(type)
    {
        sprite.setTexture(texture);
        auto texSize = texture.getSize();
        sprite.setOrigin(sf::Vector2f(texSize.x / 2.0, texSize.y / 2.0));
        sprite.setScale(sf::Vector2f(width / texSize.x, height / texSize.y));
    };
    ~CEffect() {};
};


class CCircleShape
{
public:
    double radius;
    double radiusSquared;
    sf::CircleShape circle;

    CCircleShape(double radius, const sf::Color& fill, const sf::Color& outline, const float& oThickness)
    {
        this->radius = radius;
        radiusSquared = radius * radius;
        circle = sf::CircleShape(radius);
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(oThickness);
        circle.setOrigin(sf::Vector2f(radius, radius));
    };
    ~CCircleShape() {};
};

class CLaser
{
public:
    double length;
    double lengthTgt;
    double attackAngle;
    double slip;
    double lengthNeutral;
    double lengthActive;
    double orientation = 1;
    double friction = 0.5;
    double frictionOmega = 50;
    double omega = 10;
    float laserThicknessNeutral;
    float laserThicknessActive;
    float explosionThicknessNeutral;
    float explosionThicknessActive;

    sf::Sprite laserSprite;
    sf::Sprite explosionSprite;

    CLaser(
        const double& length,
        const double& laserThickness,
        const double& explosionThickness,
        const sf::Texture& laserTexture,
        const sf::Texture& explosionTexture
    )
    :   lengthTgt(length), lengthNeutral(length), lengthActive(length * 2),
        laserThicknessNeutral(laserThickness), laserThicknessActive(laserThickness * 3),
        explosionThicknessNeutral(explosionThickness), explosionThicknessActive(explosionThickness * 2)
    {
        auto laserTexSize = laserTexture.getSize();
        laserSprite.setTexture(laserTexture);
        laserSprite.setOrigin(sf::Vector2f(laserTexSize.x / 2.0, 0));

        auto explosionTexSize = explosionTexture.getSize();
        explosionSprite.setTexture(explosionTexture);
        explosionSprite.setOrigin(sf::Vector2f(explosionTexSize.x / 2.0, explosionTexSize.y));
    };
    ~CLaser() {};
};

class CRectShape
{
public:
    sf::RectangleShape rect;

    CRectShape(const double& width, const double& height, float angle, const sf::Color& fill, const sf::Color& outline, const float& oThickness)
    {
        rect = sf::RectangleShape(sf::Vector2f(width, height));
        rect.setFillColor(fill);
        rect.setOutlineColor(outline);
        rect.setOutlineThickness(oThickness);
        rect.setOrigin(sf::Vector2f(width / 2, height / 2));
        rect.setRotation(angle);
    };
    ~CRectShape() {};
};

class CLineShape
{
public:
    bool                doubleSided;
    double              angle;
    double              angleLeft;
    double              angleRight;
    double              length;
    double              thickness;
    sf::Vertex          rect[4];

    CLineShape(const double& length, const double& thickness, float angle, const sf::Color& fill, const bool& doubleSided=true)
    :   length(length), thickness(thickness),
        angle(angle), angleLeft(angle), angleRight(angle),
        doubleSided(doubleSided)
    {
        rect[0] = sf::Vertex(sf::Vector2f(0, 0), fill);
        rect[1] = sf::Vertex(sf::Vector2f(0, 0), fill);
        rect[2] = sf::Vertex(sf::Vector2f(0, 0), fill);
        rect[3] = sf::Vertex(sf::Vector2f(0, 0), fill);
    };
    ~CLineShape() {};
};


class CCamera
{
public:
    sf::View    view;
    CameraType  type;
    double      scale = -1;
    double      xShift = 0;
    double      yWall = 3;
    double      gamma = 0.5;
    double      yGamma = 0.002;
    CCamera() {};
};