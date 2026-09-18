#pragma once

#include "Settings.h"
#include "common_inc.h"

class Map
{
public:
    Map();

    void render(sf::RenderTarget& target);

private:
    char tileAt(int x, int y);

    void renderTileWithScaledHeight(sf::RenderTarget& target, int x, int y);

    const std::string mapTiles[Settings::MAP_HEIGHT] = {
        "##################################################",
        "#                                                #",
        "#     #####                                      #",
        "#     #                                          #",
        "#     #                             ##           #",
        "#     #             ##########      ##           #",
        "#                                   ##           #",
        "#                                   #######      #",
        "#                                                #",
        "##################################################",
    };

    sf::Texture texture;
    sf::Sprite sprite;
};
