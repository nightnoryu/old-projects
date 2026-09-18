#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

float norm(const sf::Vector2f& vec);
sf::Vector2f normalized(const sf::Vector2f& vec);

sf::Vector2f topLeftPosition(const sf::Vector2f& centerPosition, float width, float height);
sf::Vector2f calculateMovementPosition(const sf::Vector2f& currentPosition,
    const sf::Vector2f& direction,
    float speed,
    float dt);
