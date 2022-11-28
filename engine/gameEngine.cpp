#include "gameEngine.hpp"


void GameEngine::run()
{
    auto start = std::chrono::high_resolution_clock::now();
    // auto elapsed = start;
    int stepsCount;
    // Main loop
    while(m_running)
    {
        // Process user input
        sUserInput();

        currentScene()->update();

        // Render every so often
        if (stepsCount % STEPS_PER_FRAME == 0)
        {
            currentScene()->sRender();

            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            usleep(std::max(DELTA_T_us * STEPS_PER_FRAME - std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count(), long(0)));
            start = std::chrono::high_resolution_clock::now();
        }

        stepsCount++;
    }
}


GameEngine::GameEngine()
{
    // Create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    m_window.create(
        sf::VideoMode(1280, 720),
        "Game",
        sf::Style::Close,
        settings
    );

    // Load assets
    m_assets.load("resource/assets.json");
}

GameEngine::~GameEngine()
{
    // Close window
    m_window.close();
}


void GameEngine::changeScene(const std::string newSceneName)
{
    m_currentScene = newSceneName;
}

void GameEngine::addScene(const std::string newSceneName, std::shared_ptr<Scene> scene)
{
    if (m_currentScene == "")
        m_currentScene = newSceneName;
    m_scenes[newSceneName] = scene;
}

void GameEngine::quit()
{
    m_running = false;
}


std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_scenes[m_currentScene];
}

std::string GameEngine::currentSceneName()
{
    return m_currentScene;
}

Assets& GameEngine::assets()
{
    return m_assets;
}

sf::RenderWindow& GameEngine::window()
{
    return m_window;
}