#include "../gameEngine.hpp"

double mapRange(double x, double xFrom, double xTo, double yFrom, double yTo)
{
    x = std::max(x, xFrom);
    x = std::min(x, xTo);
    return yFrom + (x - xFrom) / (xTo - xFrom) * (yTo - yFrom);
}

struct State
{
    Vec2 vel;
    double length;
    double slip;
};

struct Derivatives
{
    Vec2 acc;
    double dLength;
    double slipVel;
};


Derivatives computeDerivatives(const std::shared_ptr<Entity>& entity, const State &state)
{
    Derivatives drvs;

    // Gravity acceleration
    if (entity->cGravity)
        drvs.acc.y += entity->cGravity->g;

    // Laser spring
    if (entity->cLaser)
    {
        double dl = state.length - entity->cLaser->lengthTgt;
        if (dl < 0)
        {
            // Spring force
            double k = entity->cLaser->omega * entity->cLaser->omega;
            double relvel = -entity->cLaser->orientation * (state.vel.x * std::tan(entity->cLaser->attackAngle) - state.vel.y);
            double laserF = -entity->cGravity->g * 0.99 + k * dl - 2 * entity->cLaser->omega * relvel;
            laserF = entity->cLaser->orientation * std::min(laserF, 0.0);

            // Friction force
            double sin = std::sin(entity->cLaser->attackAngle);
            double cos = std::cos(entity->cLaser->attackAngle);
            double tan = sin / cos;
            drvs.slipVel = state.vel.x / cos;
            double fricF = -state.slip - 2 * entity->cLaser->omega * drvs.slipVel;
            if (fricF > entity->cLaser->friction)
                fricF = entity->cLaser->friction;
            else if (fricF < -entity->cLaser->friction)
                fricF = -entity->cLaser->friction;

            // Add forces
            drvs.acc.x += -laserF * tan + fricF / cos;
            drvs.acc.y += laserF;
            
            // Reactor force
            if (entity->cReactor)
            {
                drvs.acc += entity->cReactor->force;
            }
        }
    }

    return drvs;
}


State getState(const std::shared_ptr<Entity>& entity)
{
    State state;
    state.vel = entity->cVelocity->vec;
    state.length = entity->cLaser->length;
    state.slip = entity->cLaser->slip;
    return state;
}


State changeState(const std::shared_ptr<Entity>& entity, const State& state, const Derivatives& drvs, const double& deltaT)
{
    State newState;

    // Update velocity
    newState.vel = state.vel + drvs.acc * deltaT;

    // Update slip
    double frictionK = entity->cLaser->frictionOmega * entity->cLaser->frictionOmega;
    newState.slip = state.slip + drvs.slipVel * deltaT * frictionK;
    if (newState.slip > entity->cLaser->friction)
        newState.slip = entity->cLaser->friction;
    else if (newState.slip < -entity->cLaser->friction)
        newState.slip = -entity->cLaser->friction;

    // Update length
    newState.length = state.length + drvs.dLength * deltaT;
    if (newState.length > entity->cLaser->lengthTgt)
    {
        newState.length = entity->cLaser->lengthTgt;
        newState.slip = 0;
    }
    if (newState.length < 0)
        newState.length = 0;

    return newState;
}


void GameEngine::sPhysics()
{
    double deltaT = DELTA_T_us * 0.000001;
    double deltaTSqhalf = 0.5 * deltaT * deltaT;

    // Move objects
    for (auto entity : m_entities.getEntities())
    {
        if (entity->cPosition && entity->cVelocity)
        {
            auto state = getState(entity);
            auto drvs = computeDerivatives(entity, state);
            auto newState = changeState(entity, state, drvs, deltaT);

            entity->cPosition->vec += newState.vel * deltaT + drvs.acc * deltaTSqhalf;
            entity->cVelocity->vec = newState.vel;
            entity->cLaser->slip = newState.slip;
        }
    }

    // Move camera to the player
    auto cameras = m_entities.getEntities(TAG_CAMERA);
    auto players = m_entities.getEntities(TAG_PLAYER);
    if(cameras.size() > 0)
    {
        auto camera = cameras[0];
        if(camera->cCamera->type == CAMERA_FOCUS_PLAYER && players.size() > 0)
        {
            float aspect = float(m_window.getSize().y) / float(m_window.getSize().x);
            auto player = players[players.size() - 1];
            const Vec2& pos = player->cPosition->vec;
            const Vec2& vel = player->cVelocity->vec;
            // Modify camera scale
            double tgtScale = mapRange(std::abs(vel.x), 0, 20, 20, 20);
            if (camera->cCamera->scale < 0)
                camera->cCamera->scale = tgtScale;
            else
                camera->cCamera->scale += deltaT * camera->cCamera->gamma * (tgtScale - camera->cCamera->scale);
            float width = camera->cCamera->scale;
            float height = width * aspect;
            // Move camera in front of player
            double tgtXShift = mapRange(vel.x, -10, 10, -2, 2);
            camera->cCamera->xShift += deltaT * camera->cCamera->gamma * (tgtXShift - camera->cCamera->xShift);
            Vec2& origin = camera->cPosition->vec;
            origin.x = pos.x + camera->cCamera->xShift;
            if (pos.y > origin.y + camera->cCamera->yWall)
                origin.y = pos.y - camera->cCamera->yWall;
            else if (pos.y < origin.y - camera->cCamera->yWall)
                origin.y = pos.y + camera->cCamera->yWall;
            else
                origin.y += camera->cCamera->yGamma * (pos.y - origin.y);

            camera->cCamera->view.reset(sf::FloatRect(origin.x - width * 0.5, origin.y - height * 0.5, width, height));
        }
    }
}