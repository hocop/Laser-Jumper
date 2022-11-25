#include "../entity/entityManager.hpp"


class GameEngine;


typedef std::unordered_map<int, std::string> ActionMap;


class Scene
{
private:
    EntityManager               m_entities;
    std::shared_ptr<GameEngine> m_gameEngine;
    ActionMap                   m_actionMap;

public:
    Scene(/* args */);
    ~Scene();

    void    update() = 0;
    void    sDoAction(const Action& action) = 0;
    void    sRender() = 0;

    void    registerAction(const int& key, const std::string& actionName);
};