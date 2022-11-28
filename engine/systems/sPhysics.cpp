#include "../scenes/level.hpp"
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

    // Reactor acceleration
    if (entity->cReactor)
        drvs.acc += entity->cReactor->force;

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


void Level::sPhysics()
{
    double deltaTSqhalf = 0.5 * m_deltaT * m_deltaT;

    if (!m_paused)
    {
        // Move objects
        for (auto entity : m_entities.getEntities())
        {
            if (entity->cPosition && entity->cVelocity)
            {
                auto state = getState(entity);
                auto drvs = computeDerivatives(entity, state);
                auto newState = changeState(entity, state, drvs, m_deltaT);

                entity->cPosition->vec += newState.vel * m_deltaT + drvs.acc * deltaTSqhalf;
                entity->cVelocity->vec = newState.vel;
                entity->cLaser->slip = newState.slip;
            }
        }
    }

    // Move camera to its target
    Vec2& origin = m_camera->cPosition->vec;
    if(m_camera->cCamera->target)
    {
        auto target = m_camera->cCamera->target;
        const Vec2& pos = target->cPosition->vec;
        const Vec2& vel = target->cVelocity->vec;
        // Modify camera scale
        double tgtScale = mapRange(std::abs(vel.x), 0, 2, 16, 20);
        if (m_camera->cCamera->scale < 0)
            m_camera->cCamera->scale = tgtScale;
        else
            m_camera->cCamera->scale += m_deltaT * m_camera->cCamera->gamma * (tgtScale - m_camera->cCamera->scale);
        // Move camera in front of player
        double tgtXShift = mapRange(vel.x, -10, 10, -2, 2);
        m_camera->cCamera->xShift += m_deltaT * m_camera->cCamera->gamma * (tgtXShift - m_camera->cCamera->xShift);
        origin.x = pos.x + m_camera->cCamera->xShift;
        if (pos.y > origin.y + m_camera->cCamera->yWall)
            origin.y = pos.y - m_camera->cCamera->yWall;
        else if (pos.y < origin.y - m_camera->cCamera->yWall)
            origin.y = pos.y + m_camera->cCamera->yWall;
        else
            origin.y += m_camera->cCamera->yGamma * (pos.y - origin.y);
    }
    float aspect = float(m_gameEngine->window().getSize().y) / float(m_gameEngine->window().getSize().x);
    float width = m_camera->cCamera->scale;
    float height = width * aspect;

    m_camera->cCamera->view.reset(sf::FloatRect(origin.x - width * 0.5, origin.y - height * 0.5, width, height));
}