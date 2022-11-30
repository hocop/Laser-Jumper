#include <SFML/Graphics.hpp>
#include <iostream>

#include "engine/gameEngine.hpp"
#include "engine/scenes/level.hpp"
#include "engine/scenes/mainMenu.hpp"
#include "engine/scenes/campaignMenu.hpp"


int main(int argc, char *argv[])
{
    GameEngine game;

    MainMenu mainMenu(game);
    game.addScene("main_menu", std::make_shared<MainMenu>(mainMenu));

    CampaignMenu campaignMenu(game);
    // campaignMenu.loadCampaign("resource/campaigns/main.json");
    game.addScene("campaign_menu", std::make_shared<CampaignMenu>(campaignMenu));

    Level levelHard(game);
    levelHard.loadMap("resource/campaigns/main/01/hard3.json");
    game.addScene("hard", std::make_shared<Level>(levelHard));

    Level levelDeadly(game);
    levelDeadly.loadMap("resource/campaigns/main/03/deadly3.json");
    game.addScene("deadly", std::make_shared<Level>(levelDeadly));

    game.run();
}