#include "WorldEntity.h"

#include "GameWorld.h"

uint32_t WorldEntity::_entityCount = 0;
uint32_t WorldEntity::_entityTypeCount = 0;


WorldEntity::WorldEntity() :
    _id(WorldEntity::_entityCount++),
    m_coord(0, 0),
    _vertexArray(sf::Quads, 4),
    _angle(0.0)
{
    this->_isDying = false;
    this->_alive = true;
}

WorldEntity::WorldEntity(float x, float y, float angle) :
    _id(WorldEntity::_entityCount++),
    m_coord(x, y),
    _vertexArray(sf::Quads, 4),
    _angle(angle)
{
    this->_isDying = false;
    this->_alive = true;
}

WorldEntity::WorldEntity(sf::Vector2f coord, sf::VertexArray vertexArray, float angle) :
    _id(WorldEntity::_entityCount++),
    m_coord(coord),
    _vertexArray(vertexArray),
    _angle(angle)
{
    this->_isDying = false;
    this->_alive = true;
}

WorldEntity::WorldEntity(const WorldEntity& entity)
{
    this->_id = WorldEntity::_entityCount++;
    this->_angle = entity._angle;
    this->_isDying = entity._isDying;
    this->_type = entity._type;
    this->_alive = true;
    this->_vertexArray = entity._vertexArray;
    this->m_coord = entity.m_coord;
}

bool WorldEntity::IsDying() const
{
    return this->_isDying;
}

float WorldEntity::GetAngle() const
{
    return this->_angle;
}

EntityID WorldEntity::GetID() const
{
    return this->m_globalID;
}

const sf::Vector2f& WorldEntity::GetCoord() const
{
    return this->m_coord;
}

EntityTypes WorldEntity::GetType() const
{
    return this->_type;
}

void WorldEntity::SetID(EntityID id)
{
    this->m_globalID = id;
}

void WorldEntity::Move(float vx, float vy)
{
    //accelerate
}

void WorldEntity::SetDying()
{
    this->_isDying = true;
}

void WorldEntity::Kill(GameWorld* world)
{
    // deleter
}