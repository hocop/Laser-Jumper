#pragma once


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
