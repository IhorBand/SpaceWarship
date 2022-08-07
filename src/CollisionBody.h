#pragma once

#include "PoolObject.h"
#include "WorldEntity.h"

class CollisionBody : public PoolObject<CollisionBody>
{
public:
	CollisionBody();

	void setEntity(WorldEntity* entity);
	WorldEntity* GetEntity();
private:
	WorldEntity* entity = nullptr;
};