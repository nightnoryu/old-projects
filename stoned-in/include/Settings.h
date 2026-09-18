#pragma once

#include "common_inc.h"

namespace Settings
{
    // General game settings
    constexpr int GAME_ANTIALIASING_LEVEL = 8;
    constexpr int GAME_WINDOW_WIDTH = 800;
    constexpr int GAME_WINDOW_HEIGHT = 640;
    constexpr int GAME_MAX_FPS = 60;
    const std::string GAME_WINDOW_TITLE = "Stoned In";
    const sf::Color GAME_BACKGROUND_COLOR = sf::Color(0x0, 0x0, 0x0);

    // Player settings
    constexpr int PLAYER_WIDTH = 64;
    constexpr int PLAYER_HEIGHT = 64;
    constexpr int PLAYER_TEXTURE_AMOUNT = 6;
    constexpr float PLAYER_SPEED_FACTOR = 200.f;
    const sf::Vector2f PLAYER_INITIAL_POSITION = { 100, 100 };

    // Player bullets settings
    constexpr float PLAYER_BULLET_RADIUS = 5.f;
    constexpr float PLAYER_BULLET_SPEED = 800.f;
    const sf::Color PLAYER_BULLET_COLOR = sf::Color(0xFF, 0x0, 0x0);

    // Map settings
    constexpr int MAP_WIDTH = 50;
    constexpr int MAP_HEIGHT = 10;
    constexpr char MAP_EMPTY_TILE = ' ';
    constexpr char MAP_FILLED_TILE = '#';
    constexpr int MAP_EMPTY_TILE_X = 80;
    constexpr int MAP_EMPTY_TILE_Y = 0;
    constexpr int MAP_FILLED_TILE_X = 0;
    constexpr int MAP_FILLED_TILE_Y = 16;
    constexpr int MAP_TILE_SIZE = 16;
    constexpr int MAP_HEIGHT_SCALE_FACTOR = 4;
} // namespace Settings
