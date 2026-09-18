#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    shape = sf::CircleShape();
    shape.setRadius(Settings::PLAYER_BULLET_RADIUS);
    shape.setFillColor(Settings::PLAYER_BULLET_COLOR);
    shape.setPosition(position);
    calculateSpeed(position, direction);
}

void Bullet::update(float elapsedTime)
{
    const sf::Vector2f step = speed * elapsedTime;
    const sf::Vector2f position = shape.getPosition();
    shape.setPosition(position + step);
}

bool Bullet::isInvisible() const
{
    const sf::Vector2f position = shape.getPosition();
    if (position.x < 0 || position.x > Settings::GAME_WINDOW_WIDTH)
    {
        return true;
    }
    if (position.y < 0 || position.y > Settings::GAME_WINDOW_HEIGHT)
    {
        return true;
    }
    return false;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}

void Bullet::calculateSpeed(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    sf::Vector2f directionVector = direction - position;
    speed = Utils::normalizeVector(directionVector) * Settings::PLAYER_BULLET_SPEED;
}
