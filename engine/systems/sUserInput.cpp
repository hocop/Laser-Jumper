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
                // Set view from camera
                auto cameras = m_entities.getEntities(TAG_CAMERA);
                if(cameras.size() > 0)
                {
                    sf::Vector2f clickPos(event.mouseButton.x / 1280.0 * 2 - 1, 1 - event.mouseButton.y / 720.0 * 2);
                    const sf::Transform& tr = cameras[0]->cCamera->view.getInverseTransform();
                    Vec2(clickPos).print();
                    clickPos = tr.transformPoint(clickPos);
                    Vec2(clickPos).print();
                    // Spawn player
                    spawnPlayer(clickPos);
                }
            }
        }

        // Key pressed
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Q)
            {
                m_running = false;
            }
            if (event.key.code == sf::Keyboard::X)
            {
                spawnPlayer(Vec2(300, 300));
            }
            if (event.key.code == sf::Keyboard::Y)
            {
                // Delete last player
                EntityVec& players = m_entities.getEntities(TAG_PLAYER);
                if(players.size() > 0)
                    players[players.size() - 1]->destroy();
            }
            if (event.key.code == sf::Keyboard::Space)
            {
                // Control last player
                EntityVec& players = m_entities.getEntities(TAG_PLAYER);
                if(players.size() > 0)
                    players[players.size() - 1]->cLaser->isActive = true;
            }
            if (event.key.code == sf::Keyboard::Enter)
            {
                // Reset position
                EntityVec& players = m_entities.getEntities(TAG_PLAYER);
                if(players.size() > 0)
                {
                    players[players.size() - 1]->cPosition->vec = Vec2(0, -1);
                    players[players.size() - 1]->cVelocity->vec = Vec2(0, 0);
                }
            }
        }

        // Key released
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                // Control last player
                EntityVec& players = m_entities.getEntities(TAG_PLAYER);
                if(players.size() > 0)
                    players[players.size() - 1]->cLaser->isActive = false;
            }
        }
    }
}