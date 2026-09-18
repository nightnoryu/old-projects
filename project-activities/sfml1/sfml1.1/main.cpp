#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 240, 680 }),
        "Traffic light",
        sf::Style::Default,
        sf::ContextSettings(0, 0, 8));

    window.clear(sf::Color(0x43, 0x43, 0x43));

    sf::CircleShape green(100);
    green.setPosition({ 20, 20 });
    green.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(green);

    sf::CircleShape yellow(100);
    yellow.setPosition({ 20, 240 });
    yellow.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(yellow);

    sf::CircleShape red(100);
    red.setPosition({ 20, 460 });
    red.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(red);

    window.display();

    sf::sleep(sf::seconds(5));
}
