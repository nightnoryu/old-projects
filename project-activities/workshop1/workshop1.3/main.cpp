#include <SFML/Graphics.hpp>

// === Typedefs ===

using uint = unsigned int;

// === Constants ===

constexpr uint WINDOW_WIDTH = 800;
constexpr uint WINDOW_HEIGHT = 600;
const sf::Color WINDOW_BACKGROUND_COLOR = sf::Color(0xFF, 0xFF, 0xFF);

constexpr uint CAT_SPRITE_WIDTH = 38;
constexpr uint CAT_SPRITE_HEIGHT = 35;
constexpr uint CAT_INITIAL_X = WINDOW_WIDTH / 2 - CAT_SPRITE_WIDTH;
constexpr uint CAT_INITIAL_Y = WINDOW_HEIGHT / 2 - CAT_SPRITE_HEIGHT;
const std::string CAT_TEXTURE_PATH = "cat.png";

// === Function declarations ===

void initCat(sf::Sprite& cat, sf::Texture& catTexture);
void pollEvents(sf::RenderWindow& window);
void redrawFrame(sf::RenderWindow& window, const sf::Sprite& cat);

// === Main program ===

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Cat :3",
        sf::Style::Default,
        settings);

    sf::Texture catTexture;
    sf::Sprite cat;

    initCat(cat, catTexture);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, cat);
    }
}

// === Function definitions ===

void initCat(sf::Sprite& cat, sf::Texture& catTexture)
{
    cat.setPosition(CAT_INITIAL_X, CAT_INITIAL_Y);

    if (!catTexture.loadFromFile(CAT_TEXTURE_PATH))
    {
        std::exit(1);
    }
    cat.setTexture(catTexture);
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

void redrawFrame(sf::RenderWindow& window, const sf::Sprite& cat)
{
    window.clear(WINDOW_BACKGROUND_COLOR);
    window.draw(cat);
    window.display();
}
