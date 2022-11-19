#pragma once

#include "vec2.hpp"
#include <SFML/Graphics.hpp>


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
    double bounciness;
    CCollision(const double& dampingIn=1.0) : bounciness(dampingIn) {};
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

class CEffect
{
    public:
    EffectType type;

    CEffect() {};
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
    double attackAngle;
    double slip;
    double lengthNeutral;
    double lengthActive;
    double orientation = 1;
    double friction = 0.5;
    double frictionOmega = 50;
    double omega = 10;
    bool isActive = false;
    float thicknessNeutral;
    float thicknessActive;

    sf::Sprite laserSprite;
    sf::Sprite contactSprite;

    CLaser(const double& length, const double& thickness, const sf::Texture& laserTexture, const sf::Texture& contactTexture)
    : length(length), lengthNeutral(length), lengthActive(length * 2), thicknessNeutral(thickness), thicknessActive(thickness * 1.5)
    {
        laserSprite.setTexture(laserTexture);
        contactSprite.setTexture(contactTexture);
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
    double              length;
    double              thickness;
    sf::Vertex          rect[4];

    CLineShape(const double& length, const double& thickness, float angle, const sf::Color& fill, const bool& doubleSided=true)
    : length(length), thickness(thickness), angle(angle / 180 * M_PI), doubleSided(doubleSided)
    {
        // rect = sf::RectangleShape(sf::Vector2f(length, thickness));
        // rect.setFillColor(fill);
        // rect.setOrigin(sf::Vector2f(length / 2, thickness / 2));
        // rect.setRotation(angle);
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
    CCamera() {};
};