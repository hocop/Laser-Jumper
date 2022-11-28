#include <SFML/Graphics.hpp>
#include <iostream>

#include "engine/gameEngine.hpp"
#include "engine/scenes/level.hpp"


int main(int argc, char *argv[])
{
    GameEngine game;

    Level level(game);
    level.loadMap("resource/tracks/hard/level3.json");
    level.spawnCamera(CAMERA_FOCUS_PLAYER);
    level.spawnHud();
    level.spawnPlayer(Vec2(0, -1));

    game.changeScene("level", std::make_shared<Level>(level));

    game.run();
}