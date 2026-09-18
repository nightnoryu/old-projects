#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

float toDegrees(float radians);
float positiveAngle(float angle);

float norm(const sf::Vector2f& vec);
sf::Vector2f normalized(const sf::Vector2f& vec);
