#include "GameWorld.h"

GameWorld::GameWorld()
{
    _collisionManager = new CollisionManager();
}

uint32_t GameWorld::RegisterEntityClass(AccessFunc func)
{
	this->m_accessFuncs.push_back(func);

	return static_cast<uint32_t>(this->m_accessFuncs.size());
}

void GameWorld::AddEntity(WorldEntity* entity)
{
    entity->Initialize();
	this->_entities.push_back(entity);
}

size_t GameWorld::AddPhysicEntity(CollisionBody* body)
{
    return this->_collisionManager->AddCollisionEntity(body);
}

void GameWorld::Initialize()
{
    this->_levelMap = new LevelMap(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT);
}

void GameWorld::Update(sf::Time elapsed)
{
    this->_cleanEntities();


    for (WorldEntity* entity : this->_entities)
    {
        entity->Update(*this, elapsed);
    }

    _collisionManager->Update(this);
}

void GameWorld::Draw(sf::RenderWindow* window, sf::Time elapsed)
{
    for (WorldEntity* entity : this->_entities)
    {
        entity->Draw(window, elapsed);
    }
}

WorldEntity* GameWorld::GetEntityById(EntityID entityId)
{
	uint32_t classID = (static_cast<uint32_t>(entityId >> 32)) - 1;
	uint32_t entityID = static_cast<uint32_t>(entityId);

	return this->m_accessFuncs[classID](entityID);
}

void GameWorld::_cleanEntities()
{
    std::list<WorldEntity*>::iterator it;
    for (it = this->_entities.begin(); it != this->_entities.end(); ++it)
    {
        WorldEntity* entity = *it;
        if (entity->IsDying())
        {
            it = this->_entities.erase(it);
            entity->Kill(this);
        }
        else if (entity->IsAlive() == false)
        {
            entity->SetDying();
        }

        if (_entities.size() <= 0 || it == _entities.end())
            break;
    }
}

