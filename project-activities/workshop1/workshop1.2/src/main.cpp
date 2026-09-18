#include "utils.h"

// === Typedefs ===

using uint = unsigned int;

// === Constants ===

// Window
constexpr uint WINDOW_WIDTH = 800;
constexpr uint WINDOW_HEIGHT = 600;

const sf::Color WINDOW_BACKGROUND_COLOR = sf::Color(0xFF, 0xFF, 0xFF);

// Arrow
constexpr uint ARROW_INITIAL_X = WINDOW_WIDTH / 2;
constexpr uint ARROW_INITIAL_Y = WINDOW_HEIGHT / 2;

constexpr float ARROW_BASE_WIDTH = 50.f;
constexpr float ARROW_BASE_HEIGHT = 50.f;

const sf::Color ARROW_FILL_COLOR = sf::Color(0xFF, 0xFF, 0);
const sf::Color ARROW_OUTLINE_COLOR = sf::Color(0, 0, 0);
const float ARROW_OUTLINE_THICKNESS = 2.f;

constexpr float ARROW_MAX_SPEED = 20.f;
constexpr float ARROW_MAX_ANGLE_SPEED = 90.f;

// General
constexpr float MAX_ANGLE = 360.f;

// === Function declarations ===

// Initialization
void initArrow(sf::ConvexShape& arrow);

// Events handling
void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition);
void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition);

// Rendering
void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& arrow);

// Updating
void update(sf::ConvexShape& arrow, sf::Clock& clock, const sf::Vector2f& mousePosition);
sf::Vector2f calculatePosition(const sf::Vector2f& currentPosition, const sf::Vector2<float>& direction, float dt);
float calculateRotation(float currentRotation, const sf::Vector2<float>& direction, float dt);

// === Main program ===

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Moving Arrow",
        sf::Style::Default,
        settings);

    sf::Clock clock;

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(arrow, clock, mousePosition);
        redrawFrame(window, arrow);
    }
}

// === Function definitions ===

void initArrow(sf::ConvexShape& arrow)
{
    arrow.setPointCount(7);
    arrow.setPoint(0, { -ARROW_BASE_HEIGHT, ARROW_BASE_WIDTH / 2 });
    arrow.setPoint(1, { -ARROW_BASE_HEIGHT, -(ARROW_BASE_WIDTH / 2) });
    arrow.setPoint(2, { 0, -(ARROW_BASE_WIDTH / 2) });
    arrow.setPoint(3, { 0, -ARROW_BASE_WIDTH });
    arrow.setPoint(4, { ARROW_BASE_HEIGHT, 0 });
    arrow.setPoint(5, { 0, ARROW_BASE_WIDTH });
    arrow.setPoint(6, { 0, ARROW_BASE_WIDTH / 2 });

    arrow.setFillColor(ARROW_FILL_COLOR);
    arrow.setOutlineColor(ARROW_OUTLINE_COLOR);
    arrow.setOutlineThickness(ARROW_OUTLINE_THICKNESS);

    arrow.setPosition(ARROW_INITIAL_X, ARROW_INITIAL_Y);
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event{};
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

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& arrow)
{
    window.clear(WINDOW_BACKGROUND_COLOR);
    window.draw(arrow);
    window.display();
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    mousePosition = { float(event.x), float(event.y) };
}

void update(sf::ConvexShape& arrow, sf::Clock& clock, const sf::Vector2f& mousePosition)
{
    const auto position = arrow.getPosition();
    const auto rotation = arrow.getRotation();
    const auto dt = clock.restart().asSeconds();
    const auto direction = mousePosition - position;

    const auto newPosition = calculatePosition(position, direction, dt);
    const auto newRotation = calculateRotation(rotation, direction, dt);

    arrow.setPosition(newPosition);
    arrow.setRotation(newRotation);
}

sf::Vector2f calculatePosition(const sf::Vector2f& currentPosition, const sf::Vector2<float>& direction, const float dt)
{
    const auto normalizedDirection = normalized(direction);
    if (std::isnan(normalizedDirection.x) || std::isnan(normalizedDirection.y))
    {
        return currentPosition;
    }

    return currentPosition + ARROW_MAX_SPEED * normalizedDirection * dt;
}

float calculateRotation(const float currentRotation, const sf::Vector2<float>& direction, const float dt)
{
    const auto directionRotation = positiveAngle(toDegrees(std::atan2(direction.y, direction.x)));
    const auto deltaRotation = directionRotation - currentRotation;

    float newRotation;
    if (std::abs(deltaRotation) > MAX_ANGLE - std::abs(deltaRotation))
    {
        if (deltaRotation > 0)
        {
            newRotation = currentRotation - ARROW_MAX_ANGLE_SPEED * dt;
        }
        else
        {
            newRotation = currentRotation + ARROW_MAX_ANGLE_SPEED * dt;
        }
    }
    else
    {
        if (deltaRotation > 0)
        {
            newRotation = currentRotation + ARROW_MAX_ANGLE_SPEED * dt;
        }
        else
        {
            newRotation = currentRotation - ARROW_MAX_ANGLE_SPEED * dt;
        }
    }

    return newRotation;
}
