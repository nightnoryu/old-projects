#pragma once

#include "Settings.h"
#include "Utils.h"
#include "common_inc.h"

class Bullet : public sf::Drawable
{
public:
    Bullet(const sf::Vector2f& position, const sf::Vector2f& direction);

    void update(float elapsedTime);

    bool isInvisible() const;

    Bullet& operator=(const Bullet& other) = default;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void calculateSpeed(const sf::Vector2f& position, const sf::Vector2f& direction);

    sf::CircleShape shape;
    sf::Vector2f speed;
};
