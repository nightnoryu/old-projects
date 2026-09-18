#include "utils.h"

// === Typedefs ===

using uint = unsigned int;

// === Constants ===

// Window
constexpr uint WINDOW_WIDTH = 800;
constexpr uint WINDOW_HEIGHT = 600;

const sf::Color WINDOW_BACKGROUND_COLOR = sf::Color(0xFF, 0xFF, 0xFF);

// Cat
constexpr uint CAT_SPRITE_WIDTH = 38;
constexpr uint CAT_SPRITE_HEIGHT = 35;

constexpr uint CAT_INITIAL_X = WINDOW_WIDTH / 2 - CAT_SPRITE_WIDTH;
constexpr uint CAT_INITIAL_Y = WINDOW_HEIGHT / 2 - CAT_SPRITE_HEIGHT;

const std::string CAT_TEXTURE_PATH = "assets/cat.png";

constexpr float CAT_SPEED = 250;

// Pointer
constexpr uint POINTER_SPRITE_WIDTH = 32;
constexpr uint POINTER_SPRITE_HEIGHT = 32;

const std::string POINTER_TEXTURE_PATH = "assets/red_pointer.png";

constexpr float POINTER_SPEED = 600;

// === Function declarations ===

// Initialization
void initCat(sf::Sprite& cat);
void initPointer(sf::Sprite& pointer);

// Events handling
void pollEvents(sf::RenderWindow& window, sf::Vector2f& clickPosition, bool& clicked);
void onMousePressed(const sf::Event::MouseButtonEvent& event, sf::Vector2f& clickPosition, bool& clicked);

// Rendering
void redrawFrame(sf::RenderWindow& window, const sf::Sprite& cat, const sf::Sprite& pointer, bool clicked);

// Updating
void update(sf::Sprite& cat, sf::Sprite& pointer, sf::Clock& clock, const sf::Vector2f& clickPosition, bool clicked);
sf::Vector2f calculatePointerPosition(const sf::Vector2f& clickPosition);
sf::Vector2f calculateCatPosition(const sf::Vector2f& currentPosition, const sf::Vector2f& direction, float dt);

// === Main program ===

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Cat's Moving :o",
        sf::Style::Default,
        settings);

    sf::Clock clock;

    sf::Sprite cat;
    sf::Sprite pointer;

    sf::Vector2f clickPosition;
    bool clicked = false;

    initCat(cat);
    initPointer(pointer);
    while (window.isOpen())
    {
        pollEvents(window, clickPosition, clicked);
        update(cat, pointer, clock, clickPosition, clicked);
        redrawFrame(window, cat, pointer, clicked);
    }
}

// === Function definitions ===

void initCat(sf::Sprite& cat)
{
    cat.setPosition(CAT_INITIAL_X, CAT_INITIAL_Y);

    static sf::Texture texture;
    if (!texture.loadFromFile(CAT_TEXTURE_PATH))
    {
        std::exit(1);
    }
    cat.setTexture(texture);
}

void initPointer(sf::Sprite& pointer)
{
    static sf::Texture texture;
    if (!texture.loadFromFile(POINTER_TEXTURE_PATH))
    {
        std::exit(1);
    }
    pointer.setTexture(texture);
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& clickPosition, bool& clicked)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMousePressed(event.mouseButton, clickPosition, clicked);
            break;
        default:
            break;
        }
    }
}

void onMousePressed(const sf::Event::MouseButtonEvent& event, sf::Vector2f& clickPosition, bool& clicked)
{
    if (event.button == sf::Mouse::Left)
    {
        std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

        clickPosition = { float(event.x), float(event.y) };
        if (!clicked)
        {
            clicked = true;
        }
    }
}

void redrawFrame(sf::RenderWindow& window, const sf::Sprite& cat, const sf::Sprite& pointer, bool clicked)
{
    window.clear(WINDOW_BACKGROUND_COLOR);
    if (clicked)
    {
        window.draw(pointer);
    }
    window.draw(cat);
    window.display();
}

void update(sf::Sprite& cat, sf::Sprite& pointer, sf::Clock& clock, const sf::Vector2f& clickPosition, bool clicked)
{
    const auto dt = clock.restart().asSeconds();

    const auto newPointerPosition = calculatePointerPosition(clickPosition);
    pointer.setPosition(newPointerPosition);

    if (clicked)
    {
        const auto currentCatPosition = cat.getPosition();
        const auto catDirection = newPointerPosition - currentCatPosition;

        const auto newCatPosition = calculateCatPosition(currentCatPosition, catDirection, dt);
        cat.setPosition(newCatPosition);
    }
}

sf::Vector2f calculatePointerPosition(const sf::Vector2f& clickPosition)
{
    return topLeftPosition(clickPosition, POINTER_SPRITE_WIDTH, POINTER_SPRITE_HEIGHT);
}

sf::Vector2f calculateCatPosition(const sf::Vector2f& currentPosition, const sf::Vector2f& direction, const float dt)
{
    return calculateMovementPosition(currentPosition, direction, CAT_SPEED, dt);
}
