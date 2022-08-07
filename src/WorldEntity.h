#pragma once

#include "SFML/Graphics.hpp"

#include "EntityTypes.h"

#include <cstdlib>

#define ENTITY_NULL 0

typedef uint64_t EntityID;

class GameWorld;

class WorldEntity
{
public:
	WorldEntity();
	WorldEntity(float x, float y, float angle);
	WorldEntity(sf::Vector2f coord, sf::VertexArray vertexArray, float angle);
	WorldEntity(const WorldEntity& entity);

	bool IsDying() const;
	float GetAngle() const;
	EntityID GetID() const;
	uint32_t GetPrivateID() { return _id; }
	const sf::Vector2f& GetCoord() const;
	EntityTypes GetType() const;
	sf::VertexArray& GetVertexArray() { return _vertexArray; }


	void SetID(EntityID id);
	void Move(float vx, float vy);
	void SetDying();
	
	bool IsAlive() { return this->_alive; };

	virtual void Kill(GameWorld* world);

	virtual void Collision(WorldEntity* entity, GameWorld* gameWorld) {};
	virtual void Initialize() = 0;
	virtual void Update(GameWorld& world, sf::Time elapsed) = 0;
	virtual void Draw(sf::RenderWindow* window, sf::Time elapsed) = 0;

protected:

	uint32_t _id;
	EntityID m_globalID;

	sf::VertexArray _vertexArray;
	sf::Vector2f m_coord;
	float _angle;
	bool _isDying;
	bool _alive;

	EntityTypes _type;

private:
	static uint32_t _entityCount;
	static uint32_t _entityTypeCount;
};