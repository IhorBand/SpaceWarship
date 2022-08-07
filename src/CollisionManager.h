#pragma once

#include <array>

#include "Player.h"
#include "CollisionBody.h"

class CollisionManager
{
public:
	CollisionManager();

	size_t AddCollisionEntity(CollisionBody* entity);
	void ResetIndex();
	
	CollisionBody* GetBodyByID(size_t index);
	void KillBody(size_t id);

	void Update(GameWorld* world);

private:
	std::list<CollisionBody*> _bodies;
	std::list<size_t> _bodiesID;

	int _maxIndex;

};