#include <SFML/Graphics.hpp>
#include <iostream>

#include "engine/gameEngine.hpp"
#include "engine/scenes/level.hpp"
#include "engine/scenes/mainMenu.hpp"
#include "engine/scenes/campaignMenu.hpp"


int main(int argc, char *argv[])
{

    std::string name = "noname";
    if (argc == 2)
        name = argv[1];
    GameEngine game(name);

    MainMenu mainMenu(game);
    game.addScene("main_menu", std::make_shared<MainMenu>(mainMenu));

    CampaignMenu campaignMenu(game);
    campaignMenu.load("resource/campaigns/main");
    game.addScene("campaign_menu", std::make_shared<CampaignMenu>(campaignMenu));

    game.run();
}