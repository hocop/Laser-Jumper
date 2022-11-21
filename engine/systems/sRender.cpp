#include "../gameEngine.hpp"


void GameEngine::sRender()
{
    auto players = m_entities.getEntities(TAG_PLAYER);
    auto cameras = m_entities.getEntities(TAG_CAMERA);

    // Set view from camera
    if(cameras.size() > 0)
    {
        auto camera = cameras[0];
        m_window.setView(camera->cCamera->view);
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

    // Draw effects
    for (auto entity : m_entities.getEntities(TAG_EFFECT))
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
        double dl = entity->cLaser->length - entity->cLaser->lengthTgt;
        if (dl < 0)
        {
            window.draw(entity->cLaser->explosionSprite);
        }
    }
    if (entity->cCircleShape)
        window.draw(entity->cCircleShape->circle);

    if (entity->cRectShape)
        window.draw(entity->cRectShape->rect);

    if (entity->cLineShape)
        window.draw(entity->cLineShape->rect, 4, sf::Quads);
    
    if (entity->cReactor)
        window.draw(entity->cReactor->sprite);
    
    if (entity->cEffect)
        window.draw(entity->cEffect->sprite);
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
        double dl = entity->cLaser->lengthTgt - entity->cLaser->length;
        double laserThickness = entity->cLaser->laserThicknessNeutral + dl * (entity->cLaser->laserThicknessActive - entity->cLaser->laserThicknessNeutral);
        double explosionThickness = entity->cLaser->explosionThicknessNeutral + std::sqrt(dl) * (entity->cLaser->explosionThicknessActive - entity->cLaser->explosionThicknessNeutral);

        auto laserTexSize = entity->cLaser->laserSprite.getTexture()->getSize();
        entity->cLaser->laserSprite.setScale(sf::Vector2f(laserThickness / laserTexSize.x, entity->cLaser->length / laserTexSize.y));
        entity->cLaser->laserSprite.setPosition(entity->cPosition->vec.as_sf());

        auto explosionTexSize = entity->cLaser->explosionSprite.getTexture()->getSize();
        entity->cLaser->explosionSprite.setScale(sf::Vector2f(explosionThickness * 2 / explosionTexSize.x, explosionThickness / explosionTexSize.y));
        Vec2 explosionPos = entity->cPosition->vec;
        explosionPos.y += entity->cLaser->length;
        entity->cLaser->explosionSprite.setPosition(explosionPos.as_sf());
        entity->cLaser->explosionSprite.setRotation(entity->cLaser->attackAngle * 180 / M_PI);
    }

    if (entity->cEffect)
        entity->cEffect->sprite.setPosition(entity->cPosition->vec.as_sf());

    if (entity->cReactor)
        entity->cReactor->sprite.setPosition(entity->cPosition->vec.as_sf());
}