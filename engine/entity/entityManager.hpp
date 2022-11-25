#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>

#include "entity.hpp"


const Vec2 CHUNK_SIZE(1, 4);


typedef std::vector<std::shared_ptr<Entity>>                                        EntityVec;
typedef std::unordered_map<EntityTag, EntityVec>                                    EntityMap;
typedef std::unordered_map<EntityTag, std::unordered_map<std::string, EntityVec>>   ChunkMap;


class EntityManager
{
    EntityVec   m_entities;
    EntityMap   m_entityMap;
    ChunkMap    m_chunkMap;
    EntityVec   m_toAdd;
    size_t      m_totalEntities = 0;
public:
    EntityManager() {};
    ~EntityManager() {};
    std::shared_ptr<Entity> addEntity(const EntityTag& tag);
    void update();
    EntityVec& getEntities();
    EntityVec& getEntities(const EntityTag& tag);
    EntityVec& getEntities(const EntityTag& tag, const std::string& coordKey);
};


std::string coordinateToKey(const Vec2 &pos);
std::vector<std::string> coordinateToKeys(const Vec2& pos, const Vec2& size);