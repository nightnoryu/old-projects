#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eyes
{
    sf::ConvexShape leftEye;
    sf::ConvexShape rightEye;
    sf::ConvexShape leftPupil;
    sf::ConvexShape rightPupil;

    sf::Vector2f position;

    float leftPupilRotation = 0;
    float rightPupilRotation = 0;
};

void initEyeEllipse(sf::ConvexShape& eye)
{
    constexpr int pointCount = 200;
    const sf::Vector2f eyeEllipseRadius = { 70.f, 130.f };
    eye.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            eyeEllipseRadius.x * std::sin(angle),
            eyeEllipseRadius.y * std::cos(angle)
        };
        eye.setPoint(pointNo, point);
    }
    eye.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
}

void initEyePupil(sf::ConvexShape& pupil)
{
    constexpr int pointCount = 200;
    constexpr float eyePupilRadius = 25.f;
    pupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            eyePupilRadius * std::sin(angle),
            eyePupilRadius * std::cos(angle)
        };
        pupil.setPoint(pointNo, point);
    }
    pupil.setFillColor(sf::Color(0, 0, 0));
}

void initEyes(Eyes& eyes)
{
    eyes.position = { 400, 300 };

    initEyeEllipse(eyes.leftEye);
    eyes.leftEye.setPosition(eyes.position.x - 90, eyes.position.y);
    initEyeEllipse(eyes.rightEye);
    eyes.rightEye.setPosition(eyes.position.x + 90, eyes.position.y);

    initEyePupil(eyes.leftPupil);
    eyes.leftPupil.setPosition(eyes.position.x - 90, eyes.position.y);
    initEyePupil(eyes.rightPupil);
    eyes.rightPupil.setPosition(eyes.position.x + 90, eyes.position.y);
}

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        radius * std::cos(angle),
        radius * std::sin(angle)
    };
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void updateEyes(Eyes& eyes)
{
    const sf::Vector2f leftPupilOffset = toEuclidean(20, eyes.leftPupilRotation);
    const sf::Vector2f rightPupilOffset = toEuclidean(20, eyes.rightPupilRotation);

    eyes.leftPupil.setPosition(
        eyes.position.x - 90 + leftPupilOffset.x,
        eyes.position.y + leftPupilOffset.y);
    eyes.leftPupil.setRotation(toDegrees(eyes.leftPupilRotation));

    eyes.rightPupil.setPosition(
        eyes.position.x + 90 + rightPupilOffset.x,
        eyes.position.y + rightPupilOffset.y);
    eyes.rightPupil.setRotation(toDegrees(eyes.rightPupilRotation));
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

void update(sf::Vector2f& mousePosition, Eyes& eyes)
{
    const sf::Vector2f leftDelta = mousePosition - eyes.leftPupil.getPosition();
    const sf::Vector2f rightDelta = mousePosition - eyes.rightPupil.getPosition();

    eyes.leftPupilRotation = std::atan2(leftDelta.y, leftDelta.x);
    eyes.rightPupilRotation = std::atan2(rightDelta.y, rightDelta.x);

    updateEyes(eyes);
}

void redrawFrame(sf::RenderWindow& window, Eyes& eyes)
{
    window.clear();
    window.draw(eyes.leftEye);
    window.draw(eyes.rightEye);
    window.draw(eyes.leftPupil);
    window.draw(eyes.rightPupil);
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
        "Eyes follow mouse", sf::Style::Default, settings);

    Eyes eyes;
    sf::Vector2f mousePosition;

    initEyes(eyes);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eyes);
        redrawFrame(window, eyes);
    }
}
