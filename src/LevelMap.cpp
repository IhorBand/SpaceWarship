#include "LevelMap.h"

#include "GameRender.h"
#include "PathHelper.h"

LevelMap::LevelMap() :
    _dimension(0.0, 0.0)
{
}

LevelMap::LevelMap(float width, float height) :
    _dimension(width, height),
    _vertexArray(sf::Quads, 4)
{
    _groundTextureID = GameRender::RegisterTexture(PathHelper::GetExePath() + BACKGROUND_TEXTURE_PATH, true);

    size_t scaleDown = 4;
    _vertexArray[0].texCoords = sf::Vector2f(0, 0);
    _vertexArray[1].texCoords = sf::Vector2f(scaleDown * _dimension.x, 0);
    _vertexArray[2].texCoords = sf::Vector2f(scaleDown * _dimension.x, scaleDown * _dimension.y);
    _vertexArray[3].texCoords = sf::Vector2f(0, scaleDown * _dimension.y);

    _vertexArray[0].position = sf::Vector2f(0, 0);
    _vertexArray[1].position = sf::Vector2f(_dimension.x, 0);
    _vertexArray[2].position = sf::Vector2f(_dimension.x, _dimension.y);
    _vertexArray[3].position = sf::Vector2f(0, _dimension.y);

    GameRender::InitGround(_groundTextureID, _vertexArray);
}

bool LevelMap::IsInBounds(const sf::Vector2f& coord) const
{
    return coord.x > 0 && coord.x < _dimension.x&& coord.y > 0 && coord.y < _dimension.y;
}

void LevelMap::Draw()
{
    _vertexArray[0].position = sf::Vector2f(0, 0);
    _vertexArray[1].position = sf::Vector2f(_dimension.x, 0);
    _vertexArray[2].position = sf::Vector2f(_dimension.x, _dimension.y);
    _vertexArray[3].position = sf::Vector2f(0, _dimension.y);

    GameRender::AddQuad(_groundTextureID, _vertexArray, RENDER);
}

