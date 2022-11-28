#include "../gameEngine.hpp"


void GameEngine::sUserInput()
{
    // Event handling
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Window closed
        if (event.type == sf::Event::Closed)
            m_running = false;

        // Mouse button pressed
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Get click position and spawn player
                // Vec2 clickPos = screenToWorld(Vec2(event.mouseButton.x, event.mouseButton.y));
                // spawnPlayer(clickPos);
            }
        }

        // Key pressed
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            // Find this key in the keymap
            if (currentScene()->actionMap().find(event.key.code) != currentScene()->actionMap().end())
            {
                // Determine action type
                const std::string type = (event.type == sf::Event::KeyPressed) ? "start" : "end";

                // Send action to the scene
                currentScene()->sDoAction(Action(currentScene()->actionMap()[event.key.code], type));
            }
        }
    }
}
