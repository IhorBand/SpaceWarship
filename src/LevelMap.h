#pragma once

#include "SFML/Graphics.hpp"

class LevelMap
{
public:
    LevelMap();
    LevelMap(float width, float height);

    bool IsInBounds(const sf::Vector2f& coord) const;

    size_t              GetTexture() const { return _groundTextureID; }
    const sf::Vector2f& GetDimension() const { return _dimension; }

    void Draw();

private:
    sf::Vector2f    _dimension;
    size_t          _groundTextureID;
    sf::VertexArray _vertexArray;

};
