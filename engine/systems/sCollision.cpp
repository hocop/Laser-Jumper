#include "../scenes/level.hpp"
#include "../gameEngine.hpp"


struct Collision
{
    Vec2 normal;
    double distance = 0;
};


void detectCircleAndBoxCollision(const std::shared_ptr<Entity>& circle, const std::shared_ptr<Entity>& box, Collision &col)
{
    // Get circle params
    double r = circle->cCircleShape->radius;
    double r2 = circle->cCircleShape->radiusSquared;
    // Get box params
    auto size = box->cRectShape->rect.getSize();
    double wHalf = size.x / 2, hHalf = size.y / 2;
    double angle = box->cPosition->rotation;
    // Compute circle relative position
    Vec2 relpos = circle->cPosition->vec - box->cPosition->vec;
    relpos = relpos.rotate(-angle);
    // Check distance first
    if (std::abs(relpos.x) > wHalf + r)
        return;
    if (std::abs(relpos.y) > hHalf + r)
        return;
    // Detect collision
    double distTop = relpos.y + r + hHalf;
    double distBot = hHalf - (relpos.y - r);
    double distLef = relpos.x + r + wHalf;
    double distRig = wHalf - (relpos.x - r);
    if (distRig > r && distLef > r)
    {
        if (relpos.y < 0)
        {
            if(distTop > 0)
            {
                col.normal.y = -1;
                col.distance = distTop;
            }
        }
        else if (distBot > 0)
        {
            col.normal.y = 1;
            col.distance = distBot;
        }
    }
    else if (distTop > r && distBot > r)
    {
        if (relpos.x < 0)
        {
            if(distLef > 0)
            {
                col.normal.x = -1;
                col.distance = distLef;
            }
        }
        else if (distRig > 0)
        {
            col.normal.x = 1;
            col.distance = distRig;
        }
    }
    else
    {
        for (int corner = 0; corner < 4; corner++)
        {
            double dx = (corner % 2 == 0)? -wHalf : wHalf;
            double dy = (corner / 2 == 0)? -hHalf : hHalf;
            Vec2 radVec(
                relpos.x - dx,
                relpos.y - dy
            );
            if (radVec.norm2() < r2)
            {
                col.distance = r - radVec.norm();
                col.normal = radVec / radVec.norm();
                break;
            }
        }
    }
    // Rotate normal back to world coordinates
    col.normal = col.normal.rotate(angle);
    return;
}


void detectCircleAndLineCollision(const std::shared_ptr<Entity>& circle, const std::shared_ptr<Entity>& line, Collision &col)
{
    // Get circle params
    double r = circle->cCircleShape->radius;
    double r2 = circle->cCircleShape->radiusSquared;
    // Get line params
    double lHalf = line->cLineShape->length * 0.5;
    double angle = line->cPosition->rotation;
    // Compute circle relative position
    Vec2 relpos = circle->cPosition->vec - line->cPosition->vec;
    relpos = relpos.rotate(-angle);
    // Check distance first
    if (std::abs(relpos.y) > r)
        return;
    if (std::abs(relpos.x) > lHalf + r)
        return;
    if (relpos.y > 0 && !line->cLineShape->doubleSided)
        return;
    // Detect collision
    double distTop = relpos.y + r;
    double distBot = -relpos.y + r;
    double distLef = relpos.x + r + lHalf;
    double distRig = lHalf - (relpos.x - r);
    if (distRig > r && distLef > r)
    {
        if (relpos.y < 0)
        {
            if(distTop > 0)
            {
                col.normal.y = -1;
                col.distance = distTop;
            }
        }
        else if (distBot > 0)
        {
            col.normal.y = 1;
            col.distance = distBot;
        }
    }
    else
    {
        for (int corner = 0; corner < 2; corner++)
        {
            double dx = (corner % 2 == 0)? -lHalf : lHalf;
            Vec2 radVec(
                relpos.x - dx,
                relpos.y
            );
            if (radVec.norm2() < r2)
            {
                col.distance = r - radVec.norm();
                col.normal = radVec / radVec.norm();
                break;
            }
        }
    }
    // Rotate normal back to world coordinates
    col.normal = col.normal.rotate(angle);
}


void detectLaserAndLineCollision(const std::shared_ptr<Entity>& player, const std::shared_ptr<Entity>& line)
{
    // Compute player relative position
    Vec2 relpos = player->cPosition->vec - line->cPosition->vec;
    // Get line params
    const double& angle = line->cPosition->rotation;
    double l = line->cLineShape->length * std::cos(angle);
    double lHalf = l * 0.5;
    double coefRight = relpos.x / l + 0.5;
    double angleInterp = line->cLineShape->angleLeft * (1 - coefRight) + line->cLineShape->angleRight * coefRight;
    // Detect collision
    if (relpos.x >= -lHalf && relpos.x <= lHalf)
    {
        double l = player->cLaser->orientation * (relpos.x * std::tan(angle) - relpos.y);
        if (l > 0 && l < player->cLaser->length)
        {
            player->cLaser->length = l;
            player->cLaser->attackAngle = angleInterp;
        }
    }
}

// Apply effect to player
void Level::applyEffect(std::shared_ptr<Entity>& effect, std::shared_ptr<Entity>& player)
{
    switch (effect->cEffect->type)
    {
    case EFFECT_FINISH:
        if (player->cTimer)
            player->cTimer->running = false;
        if (player->cControl)
            player->cControl.reset();
        m_camera->cCamera->target.reset();
        break;
    case EFFECT_REACTOR:
        if (!player->cReactor)
            player->cReactor = std::make_shared<CReactor>(m_gameEngine->assets().getTexture("reactorOnPlayer"));
        player->cReactor->time = 0.5;
        player->cReactor->force = Vec2(10, 0).rotate(effect->cPosition->rotation);
        player->cReactor->sprite.setRotation(effect->cPosition->rotation * 180 / M_PI);
        break;
    }
}


void Level::processCollisions(std::shared_ptr<Entity>& player, std::shared_ptr<Entity>& entity)
{
    if (entity->cCollision)
    {
        Collision collision;
        // Detect collision
        if (entity->cRectShape)
            detectCircleAndBoxCollision(player, entity, collision);
        if (entity->cLineShape)
        {
            detectCircleAndLineCollision(player, entity, collision);
            detectLaserAndLineCollision(player, entity);
        }
        // Resolve collision
        if (collision.distance > 0)
        {
            // Push player from the obstacle
            if (entity->cCollision->physical)
            {
                player->cPosition->vec += collision.normal * collision.distance;
                Vec2& pvel = player->cVelocity->vec;
                pvel += collision.normal * (std::max(-(pvel * collision.normal), 0.0) * (1.0 + std::sqrt(entity->cCollision->bounciness)));
            }
            // Apply effect
            if (entity->cEffect)
                applyEffect(entity, player);
        }
    }
}


void Level::sCollision()
{
    // Player-Block interaction
    for (auto player : m_entities.getEntities(TAG_PLAYER))
    {
        // Reset player's laser
        player->cLaser->length = player->cLaser->lengthTgt + CONTACT_EPS;

        // Get player's coordinate key
        auto neighboringChunks = coordinateToKeys(player->cPosition->vec, CHUNK_SIZE);

        // Collisions
        for (auto coordKey : neighboringChunks)
        {
            for (auto block : m_entities.getEntities(TAG_BLOCK, coordKey))
                processCollisions(player, block);
            for (auto effect : m_entities.getEntities(TAG_EFFECT, coordKey))
                processCollisions(player, effect);
        }
    }
}