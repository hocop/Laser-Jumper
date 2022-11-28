#pragma once

#include "../utils/vec2.hpp"
#include <SFML/Graphics.hpp>


class Entity;


struct CButton
{
    std::string action;
    CButton(const std::string& action)
    :   action(action)
    {}
};


struct CText
{
    sf::Text text;

    CText(const sf::Font& font)
    {
        text.setFont(font);
        text.setString("Timer");
        text.setCharacterSize(24); // pixels
        text.setFillColor(sf::Color::White);
    };
    ~CText() {};
};