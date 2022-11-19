#include "../gameEngine.hpp"


void GameEngine::sRender()
{
    auto players = m_entities.getEntities(TAG_PLAYER);
    auto cameras = m_entities.getEntities(TAG_CAMERA);

    // Set view from camera
    if(cameras.size() > 0)
    {
        auto camera = cameras[0];
        // Shift camera to the player
        if(camera->cCamera->type == CAMERA_FOCUS_PLAYER && players.size() > 0)
        {
            float aspect = float(m_window.getSize().y) / float(m_window.getSize().x);
            float width  = 20;
            float height = width * aspect;
            Vec2 origin;
            origin.x = players[players.size() - 1]->cPosition->vec.x + 1;

            camera->cCamera->view.reset(sf::FloatRect(origin.x - width * 0.5, origin.y - height * 0.5, width, height));
            m_window.setView(camera->cCamera->view);
        }
    }

    m_window.clear(m_bgColor);

    // Draw players
    for (auto entity : players)
    {
        resetGeometryPosition(entity);
        drawEntity(m_window, entity);
    }
    // Draw blocks
    for (auto entity : m_entities.getEntities(TAG_BLOCK))
    {
        drawEntity(m_window, entity);
    }

    m_window.display();
}


void drawEntity(sf::RenderWindow& window, const std::shared_ptr<Entity> &entity)
{
    if (entity->cLaser)
    {
        window.draw(entity->cLaser->laserSprite);
        double dl = entity->cLaser->length - (entity->cLaser->isActive? entity->cLaser->lengthActive : entity->cLaser->lengthNeutral);
        if (dl < 0)
        {
            window.draw(entity->cLaser->contactSprite);
        }
    }
    if (entity->cCircleShape)
        window.draw(entity->cCircleShape->circle);
    if (entity->cRectShape)
        window.draw(entity->cRectShape->rect);
    if (entity->cLineShape)
        window.draw(entity->cLineShape->rect, 4, sf::Quads);
}


void resetGeometryPosition(std::shared_ptr<Entity> &entity)
{
    if (entity->cCircleShape)
        entity->cCircleShape->circle.setPosition(entity->cPosition->vec.as_sf());

    if (entity->cRectShape)
        entity->cRectShape->rect.setPosition(entity->cPosition->vec.as_sf());

    if (entity->cLineShape)
    {
        Vec2& center = entity->cPosition->vec;
        Vec2 fwd = Vec2(1, 0).rotate(entity->cLineShape->angle) * (entity->cLineShape->length * 0.5);
        Vec2 sdw = Vec2(0, 1).rotate(entity->cLineShape->angle) * (entity->cLineShape->thickness * 0.5);
        entity->cLineShape->rect[0].position = (center + fwd + sdw).as_sf();
        entity->cLineShape->rect[1].position = (center + fwd - sdw).as_sf();
        entity->cLineShape->rect[2].position = (center - fwd - sdw).as_sf();
        entity->cLineShape->rect[3].position = (center - fwd + sdw).as_sf();
    }

    if (entity->cLaser)
    {
        double thickness = entity->cLaser->isActive? entity->cLaser->thicknessActive : entity->cLaser->thicknessNeutral;

        entity->cLaser->laserSprite.setOrigin(sf::Vector2f(8, 0));
        entity->cLaser->laserSprite.setScale(sf::Vector2f(thickness / 16, entity->cLaser->length / 64));
        entity->cLaser->laserSprite.setPosition(entity->cPosition->vec.as_sf());

        entity->cLaser->contactSprite.setOrigin(sf::Vector2f(16, 16));
        entity->cLaser->contactSprite.setScale(sf::Vector2f(thickness * 2 / 16, thickness * 2 / 16));
        Vec2 contactPos = entity->cPosition->vec;
        contactPos.y += entity->cLaser->length;
        entity->cLaser->contactSprite.setPosition(contactPos.as_sf());
        entity->cLaser->contactSprite.setRotation(entity->cLaser->attackAngle * 180 / M_PI);
    }
}