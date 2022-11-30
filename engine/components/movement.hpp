#pragma once

#include "../utils/vec2.hpp"


struct CPosition
{
    public:
    Vec2 vec;
    double rotation;
    CPosition() {};
    CPosition(const Vec2& vecIn, const double& rotation=0.0) : vec(vecIn), rotation(rotation) {};
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