#include "BulletsContainer.h"

void BulletsContainer::createBullet(const sf::Vector2f position, const sf::Vector2f direction)
{
    Bullet bullet(position, direction);
    bullets.push_back(bullet);
}

void BulletsContainer::update(const float elapsedTime)
{
    for (auto& bullet : bullets)
    {
        bullet.update(elapsedTime);
    }
    removeInvisibleBullets();
}

void BulletsContainer::removeInvisibleBullets()
{
    bullets.erase(std::remove_if(bullets.begin(),
                      bullets.end(),
                      [](const Bullet& bullet) { return bullet.isInvisible(); }),
        bullets.end());
}

void BulletsContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto const& bullet : bullets)
    {
        target.draw(bullet);
    }
}
