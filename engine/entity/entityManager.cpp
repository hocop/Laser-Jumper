#include "entityManager.hpp"

std::shared_ptr<Entity> EntityManager::addEntity(const EntityTag& tag)
{
    // Create entity object
    auto entity = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    // Add entity to the vector
    m_toAdd.push_back(entity);
    // Return the shared pointer
    return entity;
}

// Remove dead entities from the given vector
std::map<EntityTag, int> removeDead(EntityVec& array)
{
    std::map<EntityTag, int> deadCount;
    for (int i = 0; i < array.size(); i++)
    {
        if (!array[i]->alive())
        {
            deadCount[array[i]->tag()]++;
            array[i] = array.back();
            array.pop_back();
        }
    }
    return deadCount;
}

std::string coordinateToKey(const Vec2& pos)
{
    int x = pos.x / CHUNK_SIZE.x;
    int y = pos.y / CHUNK_SIZE.y;
    std::stringstream ss;
    ss << x << "," << y;
    return ss.str();
}

std::vector<std::string> coordinateToKeys(const Vec2& pos, const Vec2& size)
{
    std::vector<std::string> neighboringChunks;
    for (double dx = -size.x / 2; dx <= size.x / 2; dx += CHUNK_SIZE.x)
        for (double dy = -size.y / 2; dy <= size.y / 2; dy += CHUNK_SIZE.y)
            neighboringChunks.push_back(coordinateToKey(pos + Vec2(dx, dy)));
    return neighboringChunks;
}

void EntityManager::update()
{
    // Add new entities
    for (auto entity : m_toAdd)
    {
        // Add entity to the vector
        m_entities.push_back(entity);
        // Add entity to the map
        m_entityMap[entity->tag()].push_back(entity);
        // Add entity to the chunk map
        if(entity->cPosition && !entity->cVelocity)
            m_chunkMap[entity->tag()][coordinateToKey(entity->cPosition->vec)].push_back(entity);
    }

    // Reset toAdd buffer
    m_toAdd.clear();

    // Remove dead entities from the vector
    auto deadCount = removeDead(m_entities);

    // Remove dead entities from the map
    for (auto & [tag, entities] : m_entityMap)
        if (deadCount[tag])
            removeDead(entities);

    // Remove dead entities from the chunk map
    for (auto & [tag, map] : m_chunkMap)
        if (deadCount[tag])
            for (auto & [coord, entities] : map)
                removeDead(entities);
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(const EntityTag& tag)
{
    return m_entityMap[tag];
}

EntityVec& EntityManager::getEntities(const EntityTag& tag, const std::string& coordKey)
{
    return m_chunkMap[tag][coordKey];
}