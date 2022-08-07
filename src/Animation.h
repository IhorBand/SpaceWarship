#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation();
    Animation(uint32_t sheetW, uint32_t sheetH, uint32_t spriteW, uint32_t spriteH, uint32_t frameCount, float speed, bool isRepeated = true);
    void SetTextureID(uint64_t textureID);
    void SetDone(bool isDone) { _done = isDone; }
    void SetCenter(sf::Vector2f center) { _spriteCenter = center; }
    void ResetTime(float time);

    sf::IntRect  GetTexCoord(float time);
    sf::Vector2f GetSpriteSize()   const { return sf::Vector2f(static_cast<float>(_spriteW), static_cast<float>(_spriteH)); }
    sf::Vector2f GetSpriteCenter() const { return _spriteCenter; }
    uint64_t GetTexture()      const { return _textureID; }
    uint64_t GetCurrentIndex(float time) const { return static_cast<size_t>(_animationSpeed * (time - _startTime)); }
    bool IsRepeated() { return _isRepeated; }

    void ApplyOnQuad(sf::VertexArray& quad, float time);

    bool IsDone() const;
    
private:
    uint32_t _sheetW;
    uint32_t _sheetH;
    uint32_t _spriteW;
    uint32_t _spriteH;

    float  _startTime;

    uint32_t _frameCount;
    float  _animationSpeed;
    bool   _done;
    bool _isRepeated;

    sf::Vector2f _spriteCenter;
    uint64_t     _textureID;

};

