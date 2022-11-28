#pragma once

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


struct CCountdown
{
    double time = 1.0;

    CCountdown() {};
    ~CCountdown() {};
};