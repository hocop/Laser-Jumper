#include "assets.hpp"


void Assets::load(const std::string& jsonFile)
{
    std::ifstream f(jsonFile);
    json objects = json::parse(f);

    if ( sf::Shader::isAvailable() )
        std::cout << "Shaders are available on this system\n";
    else
        std::cout << "No shaders, sorry\n";

    for (auto obj : objects)
    {
        if (obj["type"] == "texture")
        {
            if (!m_textures[obj["key"]].loadFromFile(obj["path"]))
                std::cout << "Error loading texture from " << obj["path"] << std::endl;
            m_textures[obj["key"]].setSmooth(true);
        }
        else if (obj["type"] == "font")
        {
            if (!m_fonts[obj["key"]].loadFromFile(obj["path"]))
                std::cout << "Error loading texture from " << obj["path"] << std::endl;
        }
        else if (obj["type"] == "shader")
        {
            if (!m_shaders[obj["key"]].loadFromFile(obj["path"], sf::Shader::Fragment))
                std::cout << "Error loading texture from " << obj["path"] << std::endl;
        }
    }
}


const sf::Texture& Assets::getTexture(const std::string& key)
{
    if (m_textures.find(key) == m_textures.end())
        std::cout << "Cannot find texture " << key << std::endl;
    return m_textures[key];
}


const sf::Font& Assets::getFont(const std::string& key)
{
    if (m_fonts.find(key) == m_fonts.end())
        std::cout << "Cannot find font " << key << std::endl;
    return m_fonts[key];
}


sf::Shader& Assets::getShader(const std::string& key)
{
    if (m_shaders.find(key) == m_shaders.end())
        std::cout << "Cannot find shader " << key << std::endl;
    return m_shaders[key];
}


ShaderMap& Assets::getShaders()
{
    return m_shaders;
}