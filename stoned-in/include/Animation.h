#pragma once

#include "common_inc.h"

struct Frame
{
    sf::IntRect rect;
    float duration;

    explicit Frame(sf::IntRect rect)
        : rect(rect)
        , duration(0.1f)
    {
    }
};

class Animation
{
public:
    explicit Animation(sf::Sprite& sprite);

    void addFrame(Frame&& frame);

    void update(float elapsedTime);

private:
    void adjustTotalProgress(float elapsedTime);

    sf::Sprite& target;
    std::vector<Frame> frames;
    float totalLength;
    float totalProgress;
};
