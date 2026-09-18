#include "Animation.h"

Animation::Animation(sf::Sprite& sprite)
    : target(sprite)
    , totalLength(0)
    , totalProgress(0)
{
}

void Animation::addFrame(Frame&& frame)
{
    frames.push_back(frame);
    totalLength += frame.duration;
}

void Animation::update(float elapsedTime)
{
    adjustTotalProgress(elapsedTime);

    float progress = totalProgress;
    for (auto frame = frames.begin(); frame != frames.end(); ++frame)
    {
        progress -= frame->duration;

        if (progress <= 0.f || frame == frames.end())
        {
            target.setTextureRect(frame->rect);
            break;
        }
    }
}

void Animation::adjustTotalProgress(float elapsedTime)
{
    totalProgress += elapsedTime;
    if (totalProgress > totalLength)
    {
        totalProgress -= totalLength;
    }
}
