#pragma once

#include "scene.hpp"


class MainMenu : public Scene
{
private:

public:
    MainMenu(GameEngine& gameEngine);
    ~MainMenu() {};

    void update();
    void sDoAction(const Action& anction);
    void sRender();
    void reset() {};
};