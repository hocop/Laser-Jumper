#pragma once

#include "../utils/vec2.hpp"
#include <SFML/Graphics.hpp>


struct CSprite
{
    sf::Sprite sprite;

    CSprite(double width, double height, const sf::Texture& texture)
    {
        sprite.setTexture(texture);
        auto texSize = texture.getSize();
        sprite.setOrigin(sf::Vector2f(texSize.x / 2.0, texSize.y / 2.0));
        sprite.setScale(sf::Vector2f(width / texSize.x, height / texSize.y));
    };
    ~CSprite() {};
};


struct CShader
{
    sf::Shader* shader;

    CShader(sf::Shader& shader)
    {
        this->shader = &shader;
    };
    ~CShader() {};
};