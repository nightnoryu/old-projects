#include "Utils.h"

sf::Vector2f Utils::normalizeVector(const sf::Vector2f& vector)
{
    const auto lambda = static_cast<float>(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
    return vector / lambda;
}
