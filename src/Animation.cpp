#include "Animation.h"

#include <iostream>

Animation::Animation()
{
    _sheetW = 0;
    _sheetH = 0;
    _spriteW = 0;
    _spriteH = 0;
    _startTime = 0;
    _frameCount = 0;
    _animationSpeed = 0;
    _done = true;
    _textureID = 0;
    _isRepeated = true;
}

Animation::Animation(uint32_t sheetW, uint32_t sheetH, uint32_t spriteW, uint32_t spriteH, uint32_t frameCount, float speed, bool isRepeated) :
    _sheetW(sheetW),
    _sheetH(sheetH),
    _spriteW(spriteW),
    _spriteH(spriteH),
    _startTime(0),
    _frameCount(frameCount),
    _animationSpeed(speed),
    _isRepeated(isRepeated)
{
    _done = false;
    _textureID = 0;
    _spriteCenter = sf::Vector2f(spriteW/2, spriteH/2);
}

void Animation::SetTextureID(uint64_t textureID)
{
    _textureID = textureID;
}

void Animation::ResetTime(float time)
{
    _startTime = time;
}

/// Returns the texture area corresponding to the
/// current time
sf::IntRect Animation::GetTexCoord(float time)
{
    uint32_t currentSprite = uint32_t(_animationSpeed * (time - _startTime));
    if (currentSprite >= _frameCount)
        _done = true;

    currentSprite %= _frameCount;

    const int32_t textureX = currentSprite % _sheetW;
    const int32_t textureY = currentSprite / _sheetW;

    return sf::IntRect(_spriteW * textureX, _spriteH * textureY,
        _spriteW, _spriteH);
}

void Animation::ApplyOnQuad(sf::VertexArray& quad, float time)
{
    uint32_t currentSprite = uint32_t(_animationSpeed * (time - _startTime));
    if (currentSprite+1 >= _frameCount)
        _done = true;

    currentSprite %= _frameCount;

    float textureX = static_cast<float>((currentSprite % _sheetW) * _spriteW);
    float textureY = static_cast<float>((currentSprite / _sheetW) * _spriteH);

    quad[0].texCoords = sf::Vector2f(textureX, textureY);
    quad[1].texCoords = sf::Vector2f(textureX + _spriteW, textureY);
    quad[2].texCoords = sf::Vector2f(textureX + _spriteW, textureY + _spriteH);
    quad[3].texCoords = sf::Vector2f(textureX, textureY + _spriteH);
}

bool Animation::IsDone() const
{
    return _done;
}
