#include "gameEngine.hpp"



GameEngine::GameEngine() : m_bgColor(sf::Color(18, 33, 43))
{
    // Create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    m_window.create(
        sf::VideoMode(1280, 720),
        "Game",
        sf::Style::Close,
        settings
    );

    // Load textures
    if (!m_laserTexture.loadFromFile("resource/textures/laser_beam.png"))
        std::cout << "Error loading texture" << std::endl;
    if (!m_contactTexture.loadFromFile("resource/textures/contact.png"))
        std::cout << "Error loading texture" << std::endl;
}

GameEngine::~GameEngine()
{
    // Close window
    m_window.close();
}

void GameEngine::loadMap(const std::string& path)
{
    std::ifstream f(path);
    json map = json::parse(f);

    for (int i = 0; i < map["X"].size() - 1; i++)
    {
        Vec2 start(map["X"][i], map["Y"][i]);
        Vec2 end(map["X"][i + 1], map["Y"][i + 1]);

        start.y = -start.y;
        end.y = -end.y;

        Vec2 diff = end - start;
        double angle = std::atan2(diff.y, diff.x) * 180 / M_PI;
        spawnLine(0.5 * (start + end), diff.norm(), angle);
    }
}


void GameEngine::run()
{
    auto start = std::chrono::high_resolution_clock::now();
    auto prevStart = start;
    int duration;
    // Main loop
    while(m_running)
    {
        start = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(start - prevStart).count();
        // std::cout << duration << std::endl;
        usleep(std::max(DELTA_T_us - duration, 0));
        m_entities.update();
        sUserInput();
        sCollision();
        sRender();
        sPhysics();
        prevStart = start;
    }
}


std::shared_ptr<Entity> GameEngine::spawnPlayer(const Vec2& pos)
{
    // Create player
    std::shared_ptr<Entity> player = m_entities.addEntity(TAG_PLAYER);
    player->cPosition = std::make_shared<CPosition>(pos);
    player->cVelocity = std::make_shared<CVelocity>(Vec2(0, 0));
    player->cCollision = std::make_shared<CCollision>();
    player->cGravity = std::make_shared<CGravity>();

    player->cCircleShape = std::make_shared<CCircleShape>(
        CCircleShape(
            0.25,
            sf::Color(128, 0, 0, 255),
            sf::Color(128, 128, 128, 255),
            0.01
        )
    );

    player->cLaser = std::make_shared<CLaser>(
        CLaser(
            1,
            0.05,
            m_laserTexture,
            m_contactTexture
        )
    );


    resetGeometryPosition(player);
    return player;
}


std::shared_ptr<Entity> GameEngine::spawnLine(const Vec2& pos, double length, float angle, bool doubleSided)
{
    std::shared_ptr<Entity> block = m_entities.addEntity(TAG_BLOCK);
    block->cPosition = std::make_shared<CPosition>(pos);
    block->cCollision = std::make_shared<CCollision>(0.1);
    float hCoef = std::max(0.0, std::min(1.0, -0.1 * pos.y + 0.5));
    block->cLineShape = std::make_shared<CLineShape>(
        length, 0.01, angle,
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
    block->cCollision = std::make_shared<CCollision>(0.5);
    block->cRectShape = std::make_shared<CRectShape>(
        width, height, angle,
        sf::Color(76, 51, 5, 255),
        sf::Color(128, 128, 128, 255),
        0
    );

    // Set position
    resetGeometryPosition(block);

    return block;
}


std::shared_ptr<Entity> GameEngine::spawnCamera(const CameraType& focus)
{
    std::shared_ptr<Entity> camera = m_entities.addEntity(TAG_CAMERA);
    camera->cCamera = std::make_shared<CCamera>();
    camera->cCamera->type = focus;

    return camera;
}