#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;
    const sf::Vector2f origin = { 400, 320 };
    constexpr float movementRadius = 50.f;
    constexpr int movementCount = 5;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }), "Ellipse",
        sf::Style::Default, settings);
    sf::Clock clock;

    sf::ConvexShape shape;
    shape.setPosition({ origin.x + movementRadius, origin.y });
    shape.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    shape.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float radius = 200 * std::sin(6 * angle);
        sf::Vector2f point = sf::Vector2f{
            radius * std::sin(angle),
            radius * std::cos(angle),
        };
        shape.setPoint(pointNo, point);
    }

    float currentAngle = 0;
    const float deltaAngle = float(2 * M_PI) / float(movementCount);

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

        const float dt = clock.restart().asSeconds();
        currentAngle += deltaAngle * dt;
        const sf::Vector2f newPosition = sf::Vector2f{
            origin.x + movementRadius * std::cos(currentAngle),
            origin.y + movementRadius * std::sin(currentAngle)
        };
        shape.setPosition(newPosition);

        window.clear();
        window.draw(shape);
        window.display();
    }
}
