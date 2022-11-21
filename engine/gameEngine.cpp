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
    if (!m_explosionTexture.loadFromFile("resource/textures/explosion.png"))
        std::cout << "Error loading texture" << std::endl;
    if (!m_reactorRTexture.loadFromFile("resource/textures/reactor_r.png"))
        std::cout << "Error loading texture" << std::endl;
    if (!m_reactorROnPlayerTexture.loadFromFile("resource/textures/reactor_r_on_player.png"))
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
    spawnEffect(Vec2(0, -1), EFFECT_REACTOR_R);
}


void GameEngine::run()
{
    auto start = std::chrono::high_resolution_clock::now();
    // auto elapsed = start;
    int stepsCount;
    // Main loop
    while(m_running)
    {
        auto startF = std::chrono::high_resolution_clock::now();

        // Process user input
        sUserInput();

        // Add and delete entities
        m_entities.update();
        
        // Detect and process all collisions
        sCollision();

        // Render every so often
        if (stepsCount % STEPS_PER_FRAME == 0)
        {
            sRender();

            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            usleep(std::max(DELTA_T_us * STEPS_PER_FRAME - std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count(), long(0)));
            start = std::chrono::high_resolution_clock::now();
        }

        // Physics step
        sPhysics();

        // Process temporary things such as effects
        sLifetime();

        stepsCount++;
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
            0.03,
            0.1,
            m_laserTexture,
            m_explosionTexture
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
    camera->cPosition = std::make_shared<CPosition>();
    camera->cCamera->type = focus;

    return camera;
}


std::shared_ptr<Entity> GameEngine::spawnEffect(const Vec2& pos, const EffectType& type)
{
    std::shared_ptr<Entity> effect = m_entities.addEntity(TAG_EFFECT);
    effect->cPosition = std::make_shared<CPosition>(pos);
    effect->cCollision = std::make_shared<CCollision>(0, false);
    effect->cEffect = std::make_shared<CEffect>(0.75, 1, type, m_reactorRTexture);
    effect->cRectShape = std::make_shared<CRectShape>(
        0.75, 1, 0, sf::Color(255, 255, 255, 128), sf::Color(0, 0, 0, 0), 0
    );

    // Set position
    resetGeometryPosition(effect);

    return effect;
}