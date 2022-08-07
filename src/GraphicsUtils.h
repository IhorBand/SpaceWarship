#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "WorldEntity.h"
#include "Config.h"


struct GraphicsUtils
{
public:
    static void Init();
    static sf::VertexArray CreateQuad(sf::Vector2f size, sf::Vector2f center);
    static void InitQuad(sf::VertexArray& vertices, sf::Vector2f size, sf::Vector2f center, float scale = 1.0f);
    static void Transform(sf::VertexArray& vertices, sf::Vector2f t, float r);
    static void Move(sf::VertexArray& vertices, const sf::Vector2f& t);

private:
};
