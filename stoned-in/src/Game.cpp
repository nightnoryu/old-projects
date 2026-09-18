#include "Game.h"

Game::Game()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = Settings::GAME_ANTIALIASING_LEVEL;
    window.create(
        sf::VideoMode(Settings::GAME_WINDOW_WIDTH, Settings::GAME_WINDOW_HEIGHT),
        Settings::GAME_WINDOW_TITLE,
        sf::Style::Default,
        settings);
    window.setFramerateLimit(Settings::GAME_MAX_FPS);
}

void Game::loop()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            createBullet(event.mouseButton);
        }
        else
        {
            player.handleEvent(event);
        }
    }
}

void Game::update()
{
    const float elapsedTime = clock.restart().asSeconds();

    player.update(elapsedTime);
    bullets.update(elapsedTime);
}

void Game::render()
{
    window.clear(Settings::GAME_BACKGROUND_COLOR);

    map.render(window);
    window.draw(player);
    window.draw(bullets);

    window.display();
}

void Game::createBullet(const sf::Event::MouseButtonEvent& event)
{
    const auto position = player.getCenter();
    const sf::Vector2f direction = { static_cast<float>(event.x), static_cast<float>(event.y) };
    bullets.createBullet(position, direction);
}
