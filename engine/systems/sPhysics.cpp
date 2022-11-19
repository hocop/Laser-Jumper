#include "../gameEngine.hpp"


void GameEngine::sPhysics()
{
    double deltaT = DELTA_T_us * 0.000001;
    double deltaTSqhalf = 0.5 * deltaT * deltaT;

    // Move objects
    for (auto entity : m_entities.getEntities())
    {
        if (entity->cPosition && entity->cVelocity)
        {
            Vec2& pos = entity->cPosition->vec;
            Vec2& vel = entity->cVelocity->vec;
            Vec2 acc;

            // Gravity acceleration
            if (entity->cGravity)
                acc.y += entity->cGravity->g;

            // Laser spring
            if (entity->cLaser)
            {
                double dl = entity->cLaser->length - (entity->cLaser->isActive? entity->cLaser->lengthActive : entity->cLaser->lengthNeutral);
                if (dl < 0)
                {
                    // Spring force
                    double k = entity->cLaser->omega * entity->cLaser->omega;
                    double relvel = -entity->cLaser->orientation * (entity->cVelocity->vec.x * std::tan(entity->cLaser->attackAngle) - entity->cVelocity->vec.y);
                    double laserF = -entity->cGravity->g + k * dl - 2 * entity->cLaser->omega * relvel;
                    laserF = entity->cLaser->orientation * std::min(laserF, 0.0);
                    // Friction force
                    double sin = std::sin(entity->cLaser->attackAngle);
                    double cos = std::cos(entity->cLaser->attackAngle);
                    double tan = sin / cos;
                    double slipVel = vel.x / cos;
                    double frictionK = entity->cLaser->frictionOmega * entity->cLaser->frictionOmega;
                    entity->cLaser->slip += slipVel * deltaT * frictionK;
                    if (entity->cLaser->slip > entity->cLaser->friction)
                        entity->cLaser->slip = entity->cLaser->friction;
                    else if (entity->cLaser->slip < -entity->cLaser->friction)
                        entity->cLaser->slip = -entity->cLaser->friction;
                    double fricF = -entity->cLaser->slip - 2 * entity->cLaser->omega * slipVel;
                    if (fricF > entity->cLaser->friction)
                        fricF = entity->cLaser->friction;
                    else if (fricF < -entity->cLaser->friction)
                        fricF = -entity->cLaser->friction;
                    // Add forces
                    acc.x += -laserF * tan + fricF / cos;
                    acc.y += laserF;
                }
                else
                {
                    entity->cLaser->slip = 0;
                }
            }

            pos += vel * deltaT + acc * deltaTSqhalf;
            vel += acc * deltaT;
        }
    }
}