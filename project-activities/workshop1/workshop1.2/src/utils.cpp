#include "utils.h"

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

float positiveAngle(float angle)
{
    return angle < 0 ? angle + 360 : angle;
}

float norm(const sf::Vector2f& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f normalized(const sf::Vector2f& vec)
{
    return vec / norm(vec);
}
