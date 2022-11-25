#pragma once

#include "../utils/vec2.hpp"
#include <SFML/Graphics.hpp>


class Entity;


struct CHudTimer
{
    std::shared_ptr<Entity> target;
    sf::Text text;

    CHudTimer(const sf::Font& font)
    {
        text.setFont(font);
        text.setString("Timer");
        text.setCharacterSize(24); // pixels
        text.setFillColor(sf::Color::White);
    };
    ~CHudTimer() {};
};
