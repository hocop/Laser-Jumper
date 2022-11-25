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

        // Add and delete entities
        m_entities.update();
        
        // Detect and process all collisions
        sCollision();

        // Render every so often
        if (stepsCount % STEPS_PER_FRAME == 0)
        {
            sRender();

            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            usleep(std::max(DELTA_T_us * STEPS_PER_FRAME - std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count(), long(0)));
            start = std::chrono::high_resolution_clock::now();
        }

        // Physics step
        sPhysics();

        // Process temporary things such as effects
        sLifetime();

        stepsCount++;
    }
}


GameEngine::GameEngine() : m_bgColor(sf::Color(18, 33, 43))
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

    // Init constants
    m_deltaT = DELTA_T_us * 0.000001;

    // Register actions TODO: move to scene class
    registerAction(sf::Keyboard::Space,     "jump");
    registerAction(sf::Keyboard::Enter,     "restart");
    registerAction(sf::Keyboard::P,         "pause");
    registerAction(sf::Keyboard::Q,         "exit");
    registerAction(sf::Keyboard::Y,         "deleteLast");
}

GameEngine::~GameEngine()
{
    // Close window
    m_window.close();
}
