#include "CollisionBody.h"

CollisionBody::CollisionBody()
{

}

void CollisionBody::setEntity(WorldEntity* entity)
{
	this->entity = entity;
}

WorldEntity* CollisionBody::GetEntity()
{
	return this->entity;
}