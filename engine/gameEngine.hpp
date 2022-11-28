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

    std::map<std::string, std::shared_ptr<Scene>>   m_scenes;
    std::string                                     m_currentScene;

public:
    GameEngine();
    ~GameEngine();

    void run();

    void changeScene(const std::string newSceneName);
    void changeScene(const std::string newSceneName, std::shared_ptr<Scene> scene);

    void quit();

    std::shared_ptr<Scene> currentScene();
    std::string currentSceneName();
    Assets& assets();
    sf::RenderWindow& window();

    void sUserInput();
};