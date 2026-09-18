/*
 * Using iterative calculation, we need to get from analytic equation:
 * y = A * sin(w * t)
 * to the finite differences form. Let us find the differential:
 * dy = A * w * cos(w * t)dt.
 * Then, just replace all differentials with finite differences (deltas), and we're good to go.
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 800;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Wave Moving Ball");
    sf::Clock clock;

    sf::CircleShape ball(BALL_SIZE);
    ball.setPosition({ 10, 350 });
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    float time = 0;
    float speedX = 200.f;
    constexpr float amplitudeY = 80.f;
    constexpr float periodY = 2;
    constexpr float cycleFrequency = float(2 * M_PI) / periodY;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Get time difference, sum with the total time
        const float dt = clock.restart().asSeconds();
        time += dt;

        // Calculate finite differences (deltas)
        sf::Vector2f position = ball.getPosition();
        const float dx = speedX * dt;
        const float dy = amplitudeY * cycleFrequency * std::cos(cycleFrequency * time) * dt;
        const sf::Vector2f offset = { dx, dy };
        position += offset;

        // Handle bumping into the walls
        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x < 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        ball.setPosition(position);

        window.clear();
        window.draw(ball);
        window.display();
    }
}
