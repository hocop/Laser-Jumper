#include "entityManager.hpp"

std::shared_ptr<Entity> EntityManager::addEntity(EntityTag tag)
{
    // Create entity object
    auto entity = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    // Add entity to the vector
    m_toAdd.push_back(entity);
    // Return the shared pointer
    return entity;
}

void removeDead(EntityVec& array)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (!array[i]->alive())
        {
            array[i] = array.back();
            array.pop_back();
        }
    }
}

void EntityManager::update()
{
    for (auto entity : m_toAdd)
    {
        // Add entity to the vector
        m_entities.push_back(entity);
        // Add entity to the map
        m_entityMap[entity->tag()].push_back(entity);
    }
    // Remove dead entities
    removeDead(m_entities);
    for (auto & [tag, entities] : m_entityMap)
    {
        removeDead(entities);
    }
    // Reset toAdd buffer
    m_toAdd.clear();
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(EntityTag tag)
{
    return m_entityMap[tag];
}