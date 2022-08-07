#pragma once

#include <functional>
#include <list>
#include <iostream>

#include "Player.h"
#include "LevelMap.h"
#include "CollisionManager.h"

#include "SFML/Graphics.hpp"

using AccessFunc = std::function<WorldEntity* (uint32_t)>;

class GameWorld
{
public:
	GameWorld();

	uint32_t RegisterEntityClass(AccessFunc func);
	void AddEntity(WorldEntity* entity);
	size_t AddPhysicEntity(CollisionBody* body);

	void Initialize();
	void Update(sf::Time elapsed);
	void Draw(sf::RenderWindow* window, sf::Time elapsed);

	WorldEntity* GetEntityById(EntityID entityId);
	//const LevelMap& GetLevelMap()  const { return _levelMap; }

private:
	LevelMap* _levelMap = nullptr;
	CollisionManager* _collisionManager;

	std::list<WorldEntity*> _entities;
	std::vector<AccessFunc> m_accessFuncs;
	
	void _cleanEntities();
};
