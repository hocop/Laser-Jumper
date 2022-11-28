#pragma once

#include <SFML/Graphics.hpp>


struct CCollision
{
    double  bounciness;
    bool    physical;
    CCollision(const double& dampingIn=1.0, const bool& physical=true)
    :   bounciness(dampingIn), physical(physical)
    {};
};


struct CCircleShape
{
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

struct CRectShape
{
    sf::RectangleShape  rect;
    bool                visible;

    CRectShape(const double& width, const double& height, const sf::Color& fill, const sf::Color& outline, const float& oThickness)
    :   visible(true)
    {
        rect = sf::RectangleShape(sf::Vector2f(width, height));
        rect.setFillColor(fill);
        rect.setOutlineColor(outline);
        rect.setOutlineThickness(oThickness);
        rect.setOrigin(sf::Vector2f(width / 2, height / 2));
    };
    ~CRectShape() {};
};

struct CLineShape
{
    bool                doubleSided;
    double              angleLeft;
    double              angleRight;
    double              length;
    double              thickness;
    sf::Vertex          rect[4];

    CLineShape(const double& length, const double& thickness, const sf::Color& fill, const bool& doubleSided=true)
    :   length(length), thickness(thickness),
        doubleSided(doubleSided)
    {
        rect[0] = sf::Vertex(sf::Vector2f(0, 0), fill);
        rect[1] = sf::Vertex(sf::Vector2f(0, 0), fill);
        rect[2] = sf::Vertex(sf::Vector2f(0, 0), fill);
        rect[3] = sf::Vertex(sf::Vector2f(0, 0), fill);
    };
    ~CLineShape() {};
};