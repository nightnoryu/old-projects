#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ 475, 250 }),
        "Initials",
        sf::Style::Default,
        settings);

    window.clear();

    const sf::Color lettersColor = sf::Color(0xA2, 0xFF, 0x63);
    std::vector<sf::RectangleShape> shapes;

    // Letter K
    sf::RectangleShape k1;
    k1.setSize({ 20, 200 });
    k1.setPosition({ 50, 25 });
    shapes.push_back(k1);

    sf::RectangleShape k2;
    k2.setSize({ 100 * std::sqrt(2), 20 });
    k2.setPosition({ 50, 125 });
    k2.setRotation(-45);
    shapes.push_back(k2);

    sf::RectangleShape k3;
    k3.setSize({ 100 * std::sqrt(2), 20 });
    k3.setPosition({ 50, 125 });
    k3.setOrigin({ 0, 20 });
    k3.setRotation(45);
    shapes.push_back(k3);

    // Letter B
    sf::RectangleShape b1;
    b1.setSize({ 20, 200 });
    b1.setPosition({ 190, 25 });
    shapes.push_back(b1);

    sf::RectangleShape b2;
    b2.setSize({ 100, 20 });
    b2.setPosition({ 190, 25 });
    shapes.push_back(b2);

    sf::RectangleShape b3;
    b3.setSize({ 100 * std::sqrt(2), 20 });
    b3.setPosition({ 190, 125 });
    b3.setRotation(-45);
    shapes.push_back(b3);

    sf::RectangleShape b4;
    b4.setSize({ 100, 20 });
    b4.setPosition({ 190, 125 });
    shapes.push_back(b4);

    sf::RectangleShape b5;
    b5.setSize({ 100, 20 });
    b5.setPosition({ 190, 205 });
    shapes.push_back(b5);

    sf::RectangleShape b6;
    b6.setSize({ 20, 100 });
    b6.setPosition({ 280, 125 });
    shapes.push_back(b6);

    // Letter R
    sf::RectangleShape r1;
    r1.setSize({ 20, 200 });
    r1.setPosition({ 330, 25 });
    shapes.push_back(r1);

    sf::RectangleShape r2;
    r2.setSize({ 100, 20 });
    r2.setPosition({ 330, 25 });
    shapes.push_back(r2);

    sf::RectangleShape r3;
    r3.setSize({ 100 * std::sqrt(2), 20 });
    r3.setPosition({ 330, 125 });
    r3.setRotation(-45);
    shapes.push_back(r3);

    sf::RectangleShape r4;
    r4.setSize({ 100 * std::sqrt(2), 20 });
    r4.setPosition({ 330, 125 });
    r4.setOrigin({ 0, 20 });
    r4.setRotation(45);
    shapes.push_back(r4);

    for (auto shape : shapes)
    {
        shape.setFillColor(lettersColor);
        window.draw(shape);
    }
    window.display();

    sf::sleep(sf::seconds(5));
}
