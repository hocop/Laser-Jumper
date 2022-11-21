#include <SFML/Graphics.hpp>
#include <iostream>

#include "engine/gameEngine.hpp"


int main(int argc, char *argv[])
{
    GameEngine game;

    game.loadMap("resource/tracks/deadly/level3.json");

    game.spawnPlayer(Vec2(0, -1));

    game.spawnCamera(CAMERA_FOCUS_PLAYER);

    game.run();
}