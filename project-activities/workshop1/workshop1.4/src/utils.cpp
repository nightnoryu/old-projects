#include "utils.h"

float norm(const sf::Vector2f& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f normalized(const sf::Vector2f& vec)
{
    return vec / norm(vec);
}
sf::Vector2f topLeftPosition(const sf::Vector2f& centerPosition, float width, float height)
{
    return {
        centerPosition.x - width / 2,
        centerPosition.y - height / 2,
    };
}

sf::Vector2f calculateMovementPosition(const sf::Vector2f& currentPosition,
    const sf::Vector2f& direction,
    const float speed,
    const float dt)
{
    const auto normalizedDirection = normalized(direction);
    if (std::isnan(normalizedDirection.x) || std::isnan(normalizedDirection.y))
    {
        return currentPosition;
    }

    return currentPosition + speed * normalizedDirection * dt;
}
