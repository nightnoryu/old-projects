#pragma once

#include "Bullet.h"
#include "BulletsContainer.h"
#include "Map.h"
#include "Player.h"
#include "Settings.h"
#include "common_inc.h"

class Game
{
public:
    Game();

    void loop();

private:
    void handleEvents();

    void update();

    void render();

    void createBullet(const sf::Event::MouseButtonEvent& event);

    sf::RenderWindow window;
    sf::Clock clock;

    Map map;
    Player player;
    BulletsContainer bullets;
};
