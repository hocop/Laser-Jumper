#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "../../extensions/nlohmann/json.hpp"
using json = nlohmann::json;


typedef std::unordered_map<std::string, sf::Texture>    TextureMap;
typedef std::unordered_map<std::string, sf::Font>       FontMap;
typedef std::unordered_map<std::string, sf::Shader>     ShaderMap;


class Assets
{
    TextureMap  m_textures;
    FontMap     m_fonts;
    ShaderMap   m_shaders;
public:
    Assets() {};
    void load(const std::string& jsonFile);

    const sf::Texture&  getTexture(const std::string& key);
    const sf::Font&     getFont(const std::string& key);
    sf::Shader&         getShader(const std::string& key);

    ShaderMap&          getShaders();
};