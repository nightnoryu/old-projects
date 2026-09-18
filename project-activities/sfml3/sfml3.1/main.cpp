#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

constexpr float maxAngleSpeed = 15.f;

void init(sf::ConvexShape& pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, { 40, 0 });
    pointer.setPoint(1, { -20, -20 });
    pointer.setPoint(2, { -20, 20 });
    pointer.setPosition({ 400, 300 });
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& pointer, sf::Clock& clock)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = toDegrees(std::atan2(delta.y, delta.x));
    if (angle < 0)
    {
        angle += 360;
    }
    float currentAngle = pointer.getRotation();

    const float dt = clock.restart().asSeconds();

    const float angleDiff = angle - currentAngle;
    if (std::abs(angleDiff) > 360 - std::abs(angleDiff))
    {
        if (angleDiff > 0)
        {
            currentAngle -= maxAngleSpeed * dt;
        }
        else
        {
            currentAngle += maxAngleSpeed * dt;
        }
    }
    else
    {
        if (angleDiff > 0)
        {
            currentAngle += maxAngleSpeed * dt;
        }
        else
        {
            currentAngle -= maxAngleSpeed * dt;
        }
    }

    pointer.setRotation(currentAngle);
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Pointer follows mouse", sf::Style::Default, settings);
    sf::Clock clock;

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, clock);
        redrawFrame(window, pointer);
    }
}
