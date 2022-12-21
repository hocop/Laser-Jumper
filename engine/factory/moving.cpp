#include "../scenes/level.hpp"
#include "../gameEngine.hpp"


std::shared_ptr<Entity> Level::spawnCamera(const CameraType& focus)
{
    if (m_camera)
        m_camera->destroy();

    m_camera = m_entities.addEntity(TAG_CAMERA);
    m_camera->cCamera = std::make_shared<CCamera>();
    m_camera->cPosition = std::make_shared<CPosition>();
    m_camera->cCamera->type = focus;
    return m_camera;
}


std::shared_ptr<Entity> Level::spawnPlayer(const Vec2& pos)
{
    // Create player
    m_player = m_entities.addEntity(TAG_PLAYER);
    m_player->cPosition = std::make_shared<CPosition>(pos);
    m_player->cVelocity = std::make_shared<CVelocity>(Vec2(0, 0));
    m_player->cCollision = std::make_shared<CCollision>();
    m_player->cGravity = std::make_shared<CGravity>();
    m_player->cControl = std::make_shared<CControl>();

    m_player->cShader = std::make_shared<CShader>(m_gameEngine->assets().getShader("blinking"));
    // m_player->cShader = std::make_shared<CShader>("blinking");

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
            m_gameEngine->assets().getTexture("laserBeam"),
            m_gameEngine->assets().getTexture("explosion")
        )
    );

    // Bind camera to player
    if (m_camera)
        if (m_camera->cCamera->type == CAMERA_FOCUS_PLAYER)
            m_camera->cCamera->target = m_player;
    
    // Bind timer to player
    if (m_timer)
        m_player->cTimer->target = m_timer;

    resetGeometryPosition(m_player);
    return m_player;
}
