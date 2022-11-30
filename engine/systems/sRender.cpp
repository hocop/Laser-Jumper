#include "../scenes/level.hpp"
#include "../scenes/mainMenu.hpp"
#include "../gameEngine.hpp"


void Scene::sRender()
{
    auto& window = m_gameEngine->window();
    window.clear(sf::Color(33, 43, 18));

    // Draw HUD
    for (auto entity : m_entities.getEntities(TAG_HUD))
        drawEntity(window, entity);

    window.display();
}


void Level::sRender()
{
    auto& players = m_entities.getEntities(TAG_PLAYER);

    auto& window = m_gameEngine->window();
    window.clear(sf::Color(18, 33, 43));

    // Set view from camera
    window.setView(m_camera->cCamera->view);

    // Shaders' variables
    for (auto& [key, shader] : m_gameEngine->assets().getShaders())
    {
        shader.setUniform("u_time", m_time);
    }

    // Draw players
    for (auto entity : players)
    {
        resetGeometryPosition(entity);
        setShaderParams(entity);
        drawEntity(window, entity);
    }

    // Draw blocks
    for (auto entity : m_entities.getEntities(TAG_BLOCK))
        drawEntity(window, entity);

    // Draw effects
    for (auto entity : m_entities.getEntities(TAG_EFFECT))
        drawEntity(window, entity);


    // Set default view to draw HUD
    window.setView(window.getDefaultView());

    // Draw HUD
    for (auto entity : m_entities.getEntities(TAG_HUD))
        drawEntity(window, entity);

    window.display();
}


void Level::setShaderParams(std::shared_ptr<Entity>& entity)
{
    if (entity->cShader)
    {
        Vec2 center = worldToScreen(entity->cPosition->vec);
        sf::Glsl::Vec2 centerGL(center.x, center.y);
        entity->cShader->shader->setUniform("u_center", centerGL);
        entity->cShader->shader->setUniform("u_radius", float(entity->cCircleShape->radius / m_camera->cCamera->scale * m_gameEngine->window().getSize().x));
    }
}


void drawEntity(sf::RenderWindow& window, const std::shared_ptr<Entity> &entity)
{
    if (entity->cLaser)
    {
        window.draw(entity->cLaser->laserSprite);
        window.draw(entity->cLaser->explosionSprite);
    }
    if (entity->cCircleShape)
        if (entity->cShader)
            window.draw(entity->cCircleShape->circle, entity->cShader->shader);
        else
            window.draw(entity->cCircleShape->circle);

    if (entity->cRectShape)
        if (entity->cRectShape->visible)
            window.draw(entity->cRectShape->rect);

    if (entity->cLineShape)
        window.draw(entity->cLineShape->rect, 4, sf::Quads);

    if (entity->cReactor)
        window.draw(entity->cReactor->sprite);

    if (entity->cSprite)
        window.draw(entity->cSprite->sprite);

    if (entity->cText)
        window.draw(entity->cText->text);
}

void resetGeometryPosition(std::shared_ptr<Entity> &entity)
{
    if (!entity->cPosition)
    {
        std::cout << "Warning: resetting position without position\n";
        return;
    }

    if (entity->cCircleShape)
        entity->cCircleShape->circle.setPosition(entity->cPosition->vec.as_sf());

    if (entity->cRectShape)
    {
        entity->cRectShape->rect.setPosition(entity->cPosition->vec.as_sf());
        entity->cRectShape->rect.setRotation(entity->cPosition->rotation * 180 / M_PI);
    }

    if (entity->cLineShape)
    {
        Vec2& center = entity->cPosition->vec;
        Vec2 fwd = Vec2(1, 0).rotate(entity->cPosition->rotation) * (entity->cLineShape->length * 0.5);
        Vec2 sdw = Vec2(0, 1).rotate(entity->cPosition->rotation) * (entity->cLineShape->thickness * 0.5);
        entity->cLineShape->rect[0].position = (center + fwd + sdw).as_sf();
        entity->cLineShape->rect[1].position = (center + fwd - sdw).as_sf();
        entity->cLineShape->rect[2].position = (center - fwd - sdw).as_sf();
        entity->cLineShape->rect[3].position = (center - fwd + sdw).as_sf();
    }

    if (entity->cLaser)
    {
        double dl = entity->cLaser->length - entity->cLaser->lengthTgt;
        double laserThickness = entity->cLaser->laserThicknessNeutral - dl * (entity->cLaser->laserThicknessActive - entity->cLaser->laserThicknessNeutral);
        double explosionThickness;
        if (dl < 0)
            explosionThickness = entity->cLaser->explosionThicknessNeutral + std::sqrt(-dl) * (entity->cLaser->explosionThicknessActive - entity->cLaser->explosionThicknessNeutral);
        else
            explosionThickness = 0;

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

    if (entity->cSprite)
    {
        entity->cSprite->sprite.setPosition(entity->cPosition->vec.as_sf());
        entity->cSprite->sprite.setRotation(entity->cPosition->rotation * 180 / M_PI);
    }

    if (entity->cReactor)
        entity->cReactor->sprite.setPosition(entity->cPosition->vec.as_sf());
    
    if (entity->cText)
        entity->cText->text.setPosition(entity->cPosition->vec.as_sf());
}