#include <SFML/Graphics.hpp>
#include <iostream>

#include "engine/gameEngine.hpp"


int main(int argc, char *argv[])
{
    GameEngine game;

    game.loadMap("resource/tracks/hard/level3.json");

    game.spawnCamera(CAMERA_FOCUS_PLAYER);

    game.spawnHud();

    game.spawnPlayer(Vec2(0, -1));

    game.run();
}