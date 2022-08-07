#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	_maxIndex = 0;
}

size_t CollisionManager::AddCollisionEntity(CollisionBody* entity)
{
	_bodies.push_back(entity);
	_bodiesID.push_back(entity->GetIndex());
	++_maxIndex;

	return entity->GetIndex();
}

void CollisionManager::ResetIndex()
{
	_maxIndex = 0;
}

CollisionBody* CollisionManager::GetBodyByID(size_t index)
{
	return CollisionBody::GetObjectAt(static_cast<uint32_t>(index));
}

void CollisionManager::KillBody(size_t id)
{
	CollisionBody::GetObjectAt(static_cast<uint32_t>(id))->Remove();
}

void CollisionManager::Update(GameWorld* world)
{
	std::list<CollisionBody*>::iterator it;
	for (it = this->_bodies.begin(); it != this->_bodies.end(); ++it)
	{
		CollisionBody* body = *it;
		if (body->GetEntity()->IsAlive() == false)
		{
			it = this->_bodies.erase(it);
			_bodies;
		}

		if (_bodies.size() <= 0 || it == _bodies.end())
			break;

		std::list<CollisionBody*>::iterator itInner;
		for (itInner = this->_bodies.begin(); itInner != this->_bodies.end(); ++itInner)
		{
			if (it != itInner)
			{
				CollisionBody* bodyInner = *itInner;

				sf::VertexArray& entity = body->GetEntity()->GetVertexArray();
				sf::VertexArray& collidedEntity = bodyInner->GetEntity()->GetVertexArray();
				if (entity.getVertexCount() && collidedEntity.getVertexCount())
				{
					if (entity.getBounds().intersects(collidedEntity.getBounds()))
					{
						body->GetEntity()->Collision(bodyInner->GetEntity(), world);
					}
				}
			}
		}
	}
}
