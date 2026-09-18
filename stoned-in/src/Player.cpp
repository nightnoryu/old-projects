#include "Player.h"
#include "Settings.h"

Player::Player()
    : animation(sprite)
{
    if (!texture.loadFromFile("assets/dude.png"))
    {
        std::exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(Settings::PLAYER_INITIAL_POSITION);
    initializeAnimation();

    movingUp = movingDown = movingLeft = movingRight = false;
}

void Player::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        handleKeyPressed(event.key);
        break;
    case sf::Event::KeyReleased:
        handleKeyReleased(event.key);
        break;
    default:
        break;
    }
}

void Player::update(float elapsedTime)
{
    const float step = Settings::PLAYER_SPEED_FACTOR * elapsedTime;
    sf::Vector2f position = sprite.getPosition();

    if (movingUp && position.y > 0)
    {
        position.y -= step;
    }
    if (movingDown && (position.y + Settings::PLAYER_HEIGHT) < Settings::GAME_WINDOW_HEIGHT)
    {
        position.y += step;
    }
    if (movingLeft && position.x > 0)
    {
        position.x -= step;
    }
    if (movingRight && (position.x + Settings::PLAYER_WIDTH) < Settings::GAME_WINDOW_WIDTH)
    {
        position.x += step;
    }

    updateAnimation(elapsedTime);
    sprite.setPosition(position);
}

sf::Vector2f Player::getCenter() const
{
    const sf::Vector2f position = sprite.getPosition();
    return {
        position.x + static_cast<float>(Settings::PLAYER_WIDTH) / 2,
        position.y + static_cast<float>(Settings::PLAYER_HEIGHT) / 2
    };
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Player::initializeAnimation()
{
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    for (int i = 0; i < Settings::PLAYER_TEXTURE_AMOUNT; ++i)
    {
        animation.addFrame(Frame(sf::IntRect(
            i * Settings::PLAYER_WIDTH,
            0,
            Settings::PLAYER_WIDTH,
            Settings::PLAYER_HEIGHT)));
    }
}

void Player::updateAnimation(float elapsedTime)
{
    if (movingUp || movingDown || movingLeft || movingRight)
    {
        animation.update(elapsedTime);
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(0, 0, Settings::PLAYER_WIDTH, Settings::PLAYER_HEIGHT));
    }
}

void Player::handleKeyPressed(const sf::Event::KeyEvent& event)
{
    if (event.code == sf::Keyboard::W)
    {
        movingUp = true;
    }
    if (event.code == sf::Keyboard::S)
    {
        movingDown = true;
    }
    if (event.code == sf::Keyboard::A)
    {
        movingLeft = true;
    }
    if (event.code == sf::Keyboard::D)
    {
        movingRight = true;
    }
}

void Player::handleKeyReleased(const sf::Event::KeyEvent& event)
{
    if (event.code == sf::Keyboard::W)
    {
        movingUp = false;
    }
    if (event.code == sf::Keyboard::S)
    {
        movingDown = false;
    }
    if (event.code == sf::Keyboard::A)
    {
        movingLeft = false;
    }
    if (event.code == sf::Keyboard::D)
    {
        movingRight = false;
    }
}
