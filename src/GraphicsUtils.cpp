#include "GraphicsUtils.h"

void GraphicsUtils::Init()
{
}

sf::VertexArray GraphicsUtils::CreateQuad(sf::Vector2f size, sf::Vector2f center)
{
    sf::VertexArray vertices(sf::Quads, 4);

    float offsetX = center.x;
    float offsetY = center.y;

    float hx = size.x * 0.5f;
    float hy = size.y * 0.5f;

    vertices[0].position = sf::Vector2f(-hx - offsetX, -hy - offsetY);
    vertices[1].position = sf::Vector2f(hx - offsetX, -hy - offsetY);
    vertices[2].position = sf::Vector2f(hx - offsetX, hy - offsetY);
    vertices[3].position = sf::Vector2f(-hx - offsetX, hy - offsetY);

    return vertices;
}

void GraphicsUtils::InitQuad(sf::VertexArray& vertices, sf::Vector2f size, sf::Vector2f center, float scale)
{
    float offsetX = center.x * scale;
    float offsetY = center.y * scale;

    float hx = size.x * scale;
    float hy = size.y * scale;

    vertices[0].position = sf::Vector2f(-offsetX, -offsetY);
    vertices[1].position = sf::Vector2f(hx - offsetX, -offsetY);
    vertices[2].position = sf::Vector2f(hx - offsetX, hy - offsetY);
    vertices[3].position = sf::Vector2f(-offsetX, hy - offsetY);
}

void GraphicsUtils::Transform(sf::VertexArray& vertices, sf::Vector2f t, float r)
{
    float cosa = cos(r); //cos(0) 1
    float sina = sin(r); //sin(0) 0

    size_t nVertices = vertices.getVertexCount();
    for (size_t i(nVertices); i--;)
    {
        sf::Vertex& v = vertices[i];
        float x = v.position.x;
        float y = v.position.y;

        v.position.x = x * cosa - y * sina + t.x;
        v.position.y = x * sina + y * cosa + t.y;
    }
}

void GraphicsUtils::Move(sf::VertexArray& vertices, const sf::Vector2f& t)
{
    size_t nVertices = vertices.getVertexCount();
    for (size_t i(nVertices); i--;)
    {
        vertices[i].position.x += t.x;
        vertices[i].position.y += t.y;
    }
}

