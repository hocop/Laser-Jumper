#pragma once

#include "../utils/vec2.hpp"
#include <SFML/Graphics.hpp>


class Entity;


enum CameraType
{
    CAMERA_FOCUS_PLAYER,
    CAMERA_FREE
};


struct CCamera
{
    sf::View    view;
    CameraType  type;
    std::shared_ptr<Entity> target;
    double      scale = -1;
    double      xShift = 0;
    double      yWall = 3;
    double      gamma = 1.0;
    double      yGamma = 0.002;
    CCamera() {};
};