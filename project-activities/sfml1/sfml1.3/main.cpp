#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ 590, 550 }),
        "House",
        sf::Style::Default,
        settings);

    window.clear(sf::Color(0xFF, 0xFF, 0xFF));

    constexpr float houseX = 70, houseY = 280;

    const sf::Color houseColor = sf::Color(0x4D, 0x2E, 0x0B);
    const sf::Color doorColor = sf::Color(0x18, 0x17, 0x17);
    const sf::Color roofColor = sf::Color(0x5D, 0x1E, 0x17);
    const sf::Color pipeColor = sf::Color(0x3B, 0x38, 0x38);
    const sf::Color smokeColor = sf::Color(0xBF, 0xBF, 0xBF);

    // House
    sf::RectangleShape house;
    house.setSize({ 450, 235 });
    house.setPosition({ houseX, houseY });
    house.setFillColor(houseColor);
    window.draw(house);

    // Door
    sf::RectangleShape door;
    door.setSize({ 75, 160 });
    door.setPosition({ houseX + 45, houseY + 75 });
    door.setFillColor(doorColor);
    window.draw(door);

    // Roof
    sf::ConvexShape roof;
    roof.setPosition({ houseX - 50, houseY });
    roof.setPointCount(4);
    roof.setPoint(0, { 0, 0 });
    roof.setPoint(1, { 160, -120 });
    roof.setPoint(2, { 390, -120 });
    roof.setPoint(3, { 550, 0 });
    roof.setFillColor(roofColor);
    window.draw(roof);

    // Smoke
    sf::CircleShape smoke1;
    smoke1.setRadius(15);
    smoke1.setPosition({ houseX + 311, houseY - 190 });
    smoke1.setFillColor(smokeColor);
    window.draw(smoke1);
    sf::CircleShape smoke2;
    smoke2.setRadius(18);
    smoke2.setPosition({ houseX + 323, houseY - 215 });
    smoke2.setFillColor(smokeColor);
    window.draw(smoke2);
    sf::CircleShape smoke3;
    smoke3.setRadius(21);
    smoke3.setPosition({ houseX + 338, houseY - 240 });
    smoke3.setFillColor(smokeColor);
    window.draw(smoke3);
    sf::CircleShape smoke4;
    smoke4.setRadius(22);
    smoke4.setPosition({ houseX + 353, houseY - 270 });
    smoke4.setFillColor(smokeColor);
    window.draw(smoke4);

    // Pipe
    sf::RectangleShape pipe1;
    pipe1.setSize({ 33, 65 });
    pipe1.setPosition({ houseX + 300, houseY - 124 });
    pipe1.setFillColor(pipeColor);
    window.draw(pipe1);
    sf::RectangleShape pipe2;
    pipe2.setSize({ 58, 40 });
    pipe2.setPosition({ houseX + 288, houseY - 164 });
    pipe2.setFillColor(pipeColor);
    window.draw(pipe2);

    window.display();

    sf::sleep(sf::seconds(5));
}
