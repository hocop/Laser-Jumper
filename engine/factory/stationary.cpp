#include "../scenes/level.hpp"
#include "../gameEngine.hpp"



void Level::loadLandscape(const std::string& path)
{
    std::ifstream f(path);
    json landscape = json::parse(f);

    Vec2 diffPrev;
    std::shared_ptr<Entity> linePrev;

    for (int i = 0; i < landscape["X"].size() - 1; i++)
    {
        Vec2 start(landscape["X"][i], landscape["Y"][i]);
        Vec2 end(landscape["X"][i + 1], landscape["Y"][i + 1]);

        Vec2 diff = end - start;
        if (diff.x < 0)
            diff = -diff;

        if(i == 0)
            diffPrev = diff;

        double angle = std::atan2(diff.y, diff.x);
        Vec2 diffAvg = diffPrev.unit() + diff.unit();
        double angleLeft = std::atan2(diffAvg.y, diffAvg.x);

        if(i != 0)
            linePrev->cLineShape->angleRight = angleLeft;

        linePrev = spawnLine(0.5 * (start + end), diff.norm(), angle);
        linePrev->cLineShape->angleLeft = angleLeft;

        diffPrev = diff;
    }
}


std::shared_ptr<Entity> Level::spawnLine(const Vec2& pos, double length, float angle, bool doubleSided)
{
    auto block = m_entities.addEntity(TAG_BLOCK);
    block->cPosition = std::make_shared<CPosition>(pos);
    block->cPosition->rotation = angle;
    block->cCollision = std::make_shared<CCollision>(0.1);
    float hCoef = std::max(0.0, std::min(1.0, -0.1 * pos.y + 0.5));
    block->cLineShape = std::make_shared<CLineShape>(
        length, 0.01,
        sf::Color(255 * hCoef, 255 * hCoef, 200 * hCoef, 255),
        doubleSided
    );

    // Set position
    resetGeometryPosition(block);

    return block;
}


std::shared_ptr<Entity> Level::spawnRect(const Vec2& pos, double width, double height, float angle)
{
    auto block = m_entities.addEntity(TAG_BLOCK);
    block->cPosition = std::make_shared<CPosition>(pos);
    block->cPosition->rotation = angle;
    block->cCollision = std::make_shared<CCollision>(0.5);
    block->cRectShape = std::make_shared<CRectShape>(
        width, height,
        sf::Color(76, 51, 5, 255),
        sf::Color(128, 128, 128, 255),
        0
    );

    // Set position
    resetGeometryPosition(block);

    return block;
}


std::shared_ptr<Entity> Level::spawnEffect(const Vec2& pos, const EffectType& type, const double& angle)
{
    auto effect = m_entities.addEntity(TAG_EFFECT);
    effect->cPosition = std::make_shared<CPosition>(pos);
    effect->cPosition->rotation = angle / 180 * M_PI;
    effect->cCollision = std::make_shared<CCollision>(0, false);
    
    effect->cEffect = std::make_shared<CEffect>(type);

    // Add shape
    double width = 0.6, height = 1;
    effect->cRectShape = std::make_shared<CRectShape>(
        width, height, sf::Color(255, 255, 255, 128), sf::Color(0, 0, 0, 0), 0
    );
    effect->cRectShape->visible = false;

    // Add sprite
    switch (type)
    {
    case EFFECT_FINISH:
        effect->cSprite = std::make_shared<CSprite>(width, height, m_gameEngine->assets().getTexture("finish"));
        break;
    case EFFECT_REACTOR:
        effect->cSprite = std::make_shared<CSprite>(width, height, m_gameEngine->assets().getTexture("reactor"));
        break;
    }

    // Set position
    resetGeometryPosition(effect);

    return effect;
}