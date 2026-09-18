#include "Map.h"

Map::Map()
{
    if (!texture.loadFromFile("assets/tiles.png"))
    {
        std::exit(1);
    }
    sprite.setTexture(texture);
}

void Map::render(sf::RenderTarget& target)
{
    for (int y = 0; y < Settings::MAP_HEIGHT * Settings::MAP_HEIGHT_SCALE_FACTOR; y += Settings::MAP_HEIGHT_SCALE_FACTOR)
    {
        for (int x = 0; x < Settings::MAP_WIDTH; ++x)
        {
            switch (tileAt(x, y / Settings::MAP_HEIGHT_SCALE_FACTOR))
            {
            case Settings::MAP_EMPTY_TILE:
                sprite.setTextureRect(sf::IntRect(
                    Settings::MAP_EMPTY_TILE_X,
                    Settings::MAP_EMPTY_TILE_Y,
                    Settings::MAP_TILE_SIZE,
                    Settings::MAP_TILE_SIZE));
                break;
            case Settings::MAP_FILLED_TILE:
                sprite.setTextureRect(sf::IntRect(
                    Settings::MAP_FILLED_TILE_X,
                    Settings::MAP_FILLED_TILE_Y,
                    Settings::MAP_TILE_SIZE,
                    Settings::MAP_TILE_SIZE));
                break;
            default:
                break;
            }

            renderTileWithScaledHeight(target, x, y);
        }
    }
}

char Map::tileAt(int x, int y)
{
    return mapTiles[y][x];
}

void Map::renderTileWithScaledHeight(sf::RenderTarget& target, int x, int y)
{
    for (int i = 0; i < Settings::MAP_HEIGHT_SCALE_FACTOR; ++i)
    {
        sprite.setPosition(
            static_cast<float>(x * Settings::MAP_TILE_SIZE),
            static_cast<float>(y * Settings::MAP_TILE_SIZE + i * Settings::MAP_TILE_SIZE));
        target.draw(sprite);
    }
}
