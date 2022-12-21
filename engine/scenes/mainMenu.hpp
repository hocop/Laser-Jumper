#pragma once

#include "scene.hpp"


class MainMenu : public Scene
{
private:

public:
    MainMenu(GameEngine& gameEngine);
    ~MainMenu() {};

    void sDoAction(const Action& anction);
};