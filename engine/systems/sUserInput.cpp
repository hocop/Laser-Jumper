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
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            const std::string type = (event.type == sf::Event::MouseButtonPressed) ? "start" : "end";
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Get click position and spawn player
                // Vec2 clickPos = screenToWorld(Vec2(event.mouseButton.x, event.mouseButton.y));
                // spawnPlayer(clickPos);

                // Check each button
                for (auto hud : currentScene()->getHud())
                    if (hud->cButton && hud->cRectShape && hud->cPosition)
                    {
                        const Vec2& pos = hud->cPosition->vec;
                        const Vec2& size = hud->cRectShape->rect.getSize();
                        if(event.mouseButton.x >= pos.x - size.x * 0.5)
                            if(event.mouseButton.x <= pos.x + size.x * 0.5)
                                if(event.mouseButton.y >= pos.y - size.y * 0.5)
                                    if(event.mouseButton.y <= pos.y + size.y * 0.5)
                                        currentScene()->sDoAction(Action(hud->cButton->action, type));
                    }
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
