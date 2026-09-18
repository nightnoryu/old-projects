#include <SFML/Graphics.hpp>

// === Typedefs ===

using uint = unsigned int;

// === Constants ===

constexpr uint WINDOW_WIDTH = 800;
constexpr uint WINDOW_HEIGHT = 600;
const sf::Color WINDOW_BACKGROUND_COLOR = sf::Color(0xFF, 0xFF, 0xFF);

constexpr uint ARROW_INITIAL_X = WINDOW_WIDTH / 2;
constexpr uint ARROW_INITIAL_Y = WINDOW_HEIGHT / 2;
constexpr float ARROW_BASE_WIDTH = 50.f;
constexpr float ARROW_BASE_HEIGHT = 50.f;
constexpr uint ARROW_ROTATION = 15;
const sf::Color ARROW_FILL_COLOR = sf::Color(0xFF, 0xFF, 0);
const sf::Color ARROW_OUTLINE_COLOR = sf::Color(0, 0, 0);
const float ARROW_OUTLINE_THICKNESS = 2.f;

// === Function declarations ===

void initArrow(sf::ConvexShape& arrow);
void pollEvents(sf::RenderWindow& window);
void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& arrow);

// === Main program ===

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Arrow",
        sf::Style::Default,
        settings);

    sf::ConvexShape arrow;

    initArrow(arrow);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, arrow);
    }
}

// === Function definitions ===

void initArrow(sf::ConvexShape& arrow)
{
    arrow.setPointCount(7);
    arrow.setPoint(0, { -(ARROW_BASE_WIDTH / 2), ARROW_BASE_HEIGHT });
    arrow.setPoint(1, { -(ARROW_BASE_WIDTH / 2), 0 });
    arrow.setPoint(2, { -ARROW_BASE_WIDTH, 0 });
    arrow.setPoint(3, { 0, -ARROW_BASE_HEIGHT });
    arrow.setPoint(4, { ARROW_BASE_WIDTH, 0 });
    arrow.setPoint(5, { ARROW_BASE_WIDTH / 2, 0 });
    arrow.setPoint(6, { ARROW_BASE_WIDTH / 2, ARROW_BASE_HEIGHT });

    arrow.setPosition(ARROW_INITIAL_X, ARROW_INITIAL_Y);
    arrow.setFillColor(ARROW_FILL_COLOR);
    arrow.setOutlineColor(ARROW_OUTLINE_COLOR);
    arrow.setOutlineThickness(ARROW_OUTLINE_THICKNESS);
    arrow.setRotation(ARROW_ROTATION);
}

void pollEvents(sf::RenderWindow& window)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
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
