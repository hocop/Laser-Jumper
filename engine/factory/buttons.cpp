#include "../gameEngine.hpp"
#include "../scenes/scene.hpp"


std::shared_ptr<Entity> Scene::spawnButtonRect(const std::string& text, const std::string& action, const Vec2& pos, const Vec2& size)
{
    Vec2 ws = m_gameEngine->window().getSize();
    Vec2 sizeReal(size.x * ws.y, size.y * ws.y);

    auto button = m_entities.addEntity(TAG_HUD);
    button->cButton = std::make_shared<CButton>(action);
    button->cRectShape = std::make_shared<CRectShape>(
        sizeReal.x, sizeReal.y,
        sf::Color(76, 51, 5, 255),
        sf::Color(128, 128, 128, 255),
        0
    );

    button->cPosition = std::make_shared<CPosition>(Vec2(pos.x * ws.x + sizeReal.x / 2, pos.y * ws.y + sizeReal.y / 2));

    button->cText = std::make_shared<CText>(m_gameEngine->assets().getFont("regular"));
    button->cText->text.setString(text);
    auto textBox = button->cText->text.getGlobalBounds();
    button->cText->text.setOrigin(sf::Vector2f(textBox.width / 2.0, textBox.height / 2.0));

    resetGeometryPosition(button);

    return button;
}