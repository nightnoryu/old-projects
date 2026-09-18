#pragma once

#include "Animation.h"
#include "common_inc.h"

class Player : public sf::Drawable
{
public:
    Player();

    void handleEvent(const sf::Event& event);

    void update(float elapsedTime);

    sf::Vector2f getCenter() const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void initializeAnimation();

    void updateAnimation(float elapsedTime);

    void handleKeyPressed(const sf::Event::KeyEvent& event);

    void handleKeyReleased(const sf::Event::KeyEvent& event);

    sf::Texture texture;
    sf::Sprite sprite;
    Animation animation;
    bool movingUp;
    bool movingDown;
    bool movingLeft;
    bool movingRight;
};
