#pragma once

#include "../utils/vec2.hpp"
#include <SFML/Graphics.hpp>


struct CScreenPosition
{
    public:
    Vec2 vec;
    CScreenPosition() {};
    CScreenPosition(const Vec2& vecIn) : vec(vecIn) {};
};

struct CPosition
{
    public:
    Vec2 vec;
    double rotation;
    CPosition() {};
    CPosition(const Vec2& vecIn) : vec(vecIn) {};
};

struct CVelocity
{
    public:
    Vec2 vec;
    CVelocity() {};
    CVelocity(const Vec2& vecIn) : vec(vecIn) {};
};

struct CGravity
{
    public:
    double g = 9.8;
};