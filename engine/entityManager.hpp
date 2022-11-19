#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <vector>

#include "entity.hpp"


typedef std::vector<std::shared_ptr<Entity>>    EntityVec;
typedef std::map<EntityTag, EntityVec>          EntityMap;


class EntityManager
{
    EntityVec   m_entities;
    EntityMap   m_entityMap;
    EntityVec   m_toAdd;
    size_t      m_totalEntities = 0;
public:
    EntityManager() {};
    ~EntityManager() {};
    std::shared_ptr<Entity> addEntity(EntityTag tag);
    void update();
    EntityVec& getEntities();
    EntityVec& getEntities(EntityTag tag);
};