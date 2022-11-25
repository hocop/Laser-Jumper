#include "scene.hpp"


Scene::Scene(/* args */)
{
}

Scene::~Scene()
{
}

Scene::registerAction(const int& key, const std::string& actionName)
{
    m_actionMap[key] = actionName;
}