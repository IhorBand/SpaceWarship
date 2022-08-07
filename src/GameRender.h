#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

#include "WorldEntity.h"
#include "Config.h"
#include "GraphicsUtils.h"

enum RenderLayer
{
    GROUND = 0,
    BULLETS = 1,
    RENDER = 2,
    RenderLayer_SIZE = RENDER +1
};

class GameRender
{
public:
    static void Initialize(size_t width, size_t height);
    static void SetFocus(const sf::Vector2f& focus);
    static void Clear();
    static void AddQuad(size_t textureID, const sf::VertexArray& quad, RenderLayer layer);
    static void Display(sf::RenderTarget* target);
    static void InitGround(size_t textureID, sf::VertexArray& quad);
    static void RenderGround();
    static void FadeGround();

    static void RenderVertexArray(const sf::VertexArray& va, sf::RenderTexture& target);
    static void RenderVertexArray(const sf::VertexArray& va, sf::RenderTexture& target, sf::RenderStates states);
    static void RenderVertexArray(const sf::VertexArray& va, sf::RenderTexture& target, size_t textureID);

    static bool   IsVisible(WorldEntity* entity);
    static bool   IsVisible(const sf::Vector2f& position, float radius);
    static size_t RegisterTexture(std::string filename, bool isRepeated = false);


private:
    GameRender();

    static GameRender* GetInstance();

    static GameRender* s_instance;

    static void        _renderVertices(std::vector<sf::VertexArray>& vertices, sf::RenderTexture& target, sf::RenderStates& states);
    float              _quality, _zoom, _ratio;
    size_t             _groundTextureID;
    sf::Vector2u       _renderSize;
    sf::Vector2f       _focus;
    sf::Vector2f       _baseOffset;
    sf::VertexArray    _groundQuad;
    sf::RenderTexture  _renderTexture;
    sf::RenderTexture  _groundTexture;

    static void _translateToFocus(sf::Transform& transform);

    std::vector<sf::Texture>                  _textures;
    std::vector<std::vector<sf::VertexArray>> _vertices;
};
