#pragma once

#include "scenes/scene.hpp"

const long int DELTA_T_us = 10000;
const int STEPS_PER_FRAME = 2;

class GameEngine
{
private:
    sf::RenderWindow        m_window;
    bool                    m_running = true;
    Assets                  m_assets;
    std::string             m_playerName;

    std::map<std::string, std::shared_ptr<Scene>>   m_scenes;
    std::string                                     m_currentSceneName;

public:
    GameEngine(std::string playerName);
    ~GameEngine();

    void run();

    void changeScene(const std::string newSceneName);
    void addScene(const std::string newSceneName, std::shared_ptr<Scene> scene);

    void quit();

    std::shared_ptr<Scene>  currentScene();
    const std::string&      playerName();
    const std::string&      currentSceneName();
    Assets&                 assets();
    sf::RenderWindow&       window();

    void sUserInput();
};