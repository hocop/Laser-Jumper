#include "../gameEngine.hpp"


void GameEngine::loadMap(const std::string& path)
{
    std::ifstream f(path);
    json map = json::parse(f);

    Vec2 diffPrev;
    std::shared_ptr<Entity> linePrev;

    for (int i = 0; i < map["X"].size() - 1; i++)
    {
        Vec2 start(map["X"][i], map["Y"][i]);
        Vec2 end(map["X"][i + 1], map["Y"][i + 1]);

        start.y = -start.y;
        end.y = -end.y;

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

    // Add start booster
    spawnEffect(Vec2(0, -2), EFFECT_REACTOR);

    // Add finishes
    spawnEffect(linePrev->cPosition->vec + Vec2(0, -0.5), EFFECT_FINISH);
    spawnEffect(linePrev->cPosition->vec + Vec2(0, -1.5), EFFECT_FINISH);
    spawnEffect(linePrev->cPosition->vec + Vec2(0, -2.5), EFFECT_FINISH);
}


std::shared_ptr<Entity> GameEngine::spawnPlayer(const Vec2& pos)
{
    // Create player
    m_player = m_entities.addEntity(TAG_PLAYER);
    m_player->cPosition = std::make_shared<CPosition>(pos);
    m_player->cVelocity = std::make_shared<CVelocity>(Vec2(0, 0));
    m_player->cCollision = std::make_shared<CCollision>();
    m_player->cGravity = std::make_shared<CGravity>();

    m_player->cShader = std::make_shared<CShader>(m_assets.getShader("blinking"));

    m_player->cTimer = std::make_shared<CTimer>();

    m_player->cCircleShape = std::make_shared<CCircleShape>(
        CCircleShape(
            0.25,
            sf::Color(128, 0, 0, 255),
            sf::Color(128, 128, 128, 255),
            0.01
        )
    );

    m_player->cLaser = std::make_shared<CLaser>(
        CLaser(
            1,
            0.03,
            0.1,
            m_assets.getTexture("laserBeam"),
            m_assets.getTexture("explosion")
        )
    );

    // Bind camera to player
    if (m_camera)
        if (m_camera->cCamera->type == CAMERA_FOCUS_PLAYER)
            m_camera->cCamera->target = std::shared_ptr<Entity>(m_player);
    
    // Bind timer to player
    if (m_timer)
        m_timer->cHudTimer->target = std::shared_ptr<Entity>(m_player);

    resetGeometryPosition(m_player);
    return m_player;
}


std::shared_ptr<Entity> GameEngine::spawnLine(const Vec2& pos, double length, float angle, bool doubleSided)
{
    std::shared_ptr<Entity> block = m_entities.addEntity(TAG_BLOCK);
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


std::shared_ptr<Entity> GameEngine::spawnRect(const Vec2& pos, double width, double height, float angle)
{
    std::shared_ptr<Entity> block = m_entities.addEntity(TAG_BLOCK);
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


void GameEngine::spawnCamera(const CameraType& focus)
{
    m_camera = m_entities.addEntity(TAG_CAMERA);
    m_camera->cCamera = std::make_shared<CCamera>();
    m_camera->cPosition = std::make_shared<CPosition>();
    m_camera->cCamera->type = focus;
}


void GameEngine::spawnHud()
{
    m_timer = m_entities.addEntity(TAG_HUD);
    m_timer->cHudTimer = std::make_shared<CHudTimer>(m_assets.getFont("regular"));
}


std::shared_ptr<Entity> GameEngine::spawnEffect(const Vec2& pos, const EffectType& type, const double& angle)
{
    std::shared_ptr<Entity> effect = m_entities.addEntity(TAG_EFFECT);
    effect->cPosition = std::make_shared<CPosition>(pos);
    effect->cPosition->rotation = angle / 180 * M_PI;
    effect->cCollision = std::make_shared<CCollision>(0, false);
    const sf::Texture* tex;
    switch (type)
    {
    case EFFECT_FINISH:
        tex = &m_assets.getTexture("finish");
        break;
    case EFFECT_REACTOR:
        tex = &m_assets.getTexture("reactor");
        break;
    }
    effect->cEffect = std::make_shared<CEffect>(type);
    double width = 0.6, height = 1;
    effect->cSprite = std::make_shared<CSprite>(width, height, *tex);
    effect->cRectShape = std::make_shared<CRectShape>(
        width, height, sf::Color(255, 255, 255, 128), sf::Color(0, 0, 0, 0), 0
    );
    effect->cRectShape->visible = false;

    // Set position
    resetGeometryPosition(effect);

    return effect;
}