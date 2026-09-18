#pragma once

#include "Bullet.h"
#include "common_inc.h"

class BulletsContainer : public sf::Drawable
{
public:
    void createBullet(sf::Vector2f position, sf::Vector2f direction);

    void update(float elapsedTime);

    void removeInvisibleBullets();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<Bullet> bullets;
};
