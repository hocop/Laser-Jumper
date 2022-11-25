#pragma once

#include "../utils/vec2.hpp"
#include <SFML/Graphics.hpp>


enum EffectType
{
    EFFECT_FINISH,
    EFFECT_CHECHPOINT,
    EFFECT_REACTOR,
    EFFECT_FLIP,
    EFFECT_RESET,
    EFFECT_NOLASER
};

struct CEffect
{
    EffectType type;

    CEffect(const EffectType& type)
    :   type(type)
    {};
    ~CEffect() {};
};
