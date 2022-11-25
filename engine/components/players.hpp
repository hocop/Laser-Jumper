#pragma once

#include "../utils/vec2.hpp"
#include <SFML/Graphics.hpp>


enum ControlType
{
    CONTROL_FULL,
    CONTROL_SPLIT_L,
    CONTROL_SPLIT_R
};


struct CLaser
{
    double length;
    double lengthTgt;
    double attackAngle;
    double slip;
    double lengthNeutral;
    double lengthActive;
    double orientation = 1;
    double friction = 0.0;
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


struct CReactor
{
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


struct CTimer
{
    double timer;
    bool running;

    CTimer()
    :   timer(0), running(true)
    {};
    ~CTimer() {};
};


struct CControls
{
    public:
    ControlType type = CONTROL_FULL;

    CControls() {};
    ~CControls() {};
};


struct CReplay
{
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