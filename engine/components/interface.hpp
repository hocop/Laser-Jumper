#pragma once

#include <SFML/Graphics.hpp>


class Entity;


enum Align
{
    ALIGN_TOP,
    ALIGN_BOTTOM,
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT,
};


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
    Align vAlign;
    Align hAlign;

    CText(const sf::Font& font, const Align& hAlign=ALIGN_CENTER, const Align& vAlign=ALIGN_CENTER)
    :   vAlign(vAlign), hAlign(hAlign)
    {
        text.setFont(font);
        text.setString("Timer");
        text.setCharacterSize(24); // pixels
        text.setFillColor(sf::Color::White);
    };
    void setString(const std::string& s)
    {
        text.setString(s);
        auto textBox = text.getGlobalBounds();
        sf::Vector2f origin;
        if (hAlign == ALIGN_CENTER)
            origin.x = textBox.width / 2.0;
        else if (hAlign == ALIGN_LEFT)
            origin.x = 0.0;
        else if (hAlign == ALIGN_RIGHT)
            origin.x = textBox.width;
        else
            std::cout << "Unknown hAlign type\n";

        if (vAlign == ALIGN_CENTER)
            origin.y = textBox.height / 2.0;
        else if (vAlign == ALIGN_TOP)
            origin.y = 0.0;
        else if (vAlign == ALIGN_BOTTOM)
            origin.y = textBox.height;
        else
            std::cout << "Unknown vAlign type\n";

        text.setOrigin(origin);
    };
    ~CText() {};
};


struct CCountdown
{
    double time = 1.0;

    CCountdown() {};
    ~CCountdown() {};

    std::string getString()
    {
        if (time > 0)
            return std::to_string(int(time * 3 + 1));
        else
            return "Go!";
    };
};