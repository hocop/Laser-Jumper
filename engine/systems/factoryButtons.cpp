#include "../gameEngine.hpp"
#include "../scenes/scene.hpp"


void Scene::spawnButtonRect(const std::string& text, const std::string& action, const Vec2& pos, const Vec2& size)
{
    auto button = m_entities.addEntity(TAG_HUD);
    button->cButton = std::make_shared<CButton>(action);
    button->cRectShape = std::make_shared<CRectShape>(
        size.x, size.y,
        sf::Color(76, 51, 5, 255),
        sf::Color(128, 128, 128, 255),
        0
    );
    button->cPosition = std::make_shared<CPosition>(pos);

    button->cText = std::make_shared<CText>(m_gameEngine->assets().getFont("regular"));
    button->cText->text.setString(text);

    resetGeometryPosition(button);
}