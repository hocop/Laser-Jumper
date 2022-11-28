#include <SFML/Graphics.hpp>
#include <iostream>

#include "engine/gameEngine.hpp"
#include "engine/scenes/level.hpp"


int main(int argc, char *argv[])
{
    GameEngine game;

    Level levelHard(game);
    levelHard.loadMap("resource/tracks/hard/level3.json");
    levelHard.spawnCamera(CAMERA_FOCUS_PLAYER);
    levelHard.spawnPlayer(Vec2(0, -1));
    game.addScene("hard", std::make_shared<Level>(levelHard));

    Level levelDeadly(game);
    levelDeadly.loadMap("resource/tracks/deadly/level2.json");
    levelDeadly.spawnCamera(CAMERA_FOCUS_PLAYER);
    levelDeadly.spawnPlayer(Vec2(0, -1));
    game.addScene("deadly", std::make_shared<Level>(levelDeadly));

    // std::cout << game.currentSceneName() << std::endl;

    game.run();
}