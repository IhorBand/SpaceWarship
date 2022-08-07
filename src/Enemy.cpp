#include "Enemy.h"

uint64_t Enemy::_moveTextureID;
Animation Enemy::_moveAnimation(1, 1, 512, 512, 1, 15, true);
uint64_t Enemy::_explosionTextureID;
Animation Enemy::_explosionAnimation(17, 1, 256, 256, 17, 15, false);


Enemy::Enemy() : WorldEntity(sf::Vector2f(0, 0), sf::VertexArray(sf::Quads, 4), 0)
{
	this->_life = 100;
	this->_type = EntityTypes::ENEMY;

	this->_speed = 0.1f;

	this->_alive = true;
}

Enemy::Enemy(sf::Vector2f position): WorldEntity(position, sf::VertexArray(sf::Quads, 4), 0)
{
	this->_life = 100;
	this->_type = EntityTypes::ENEMY;

	this->_speed = 0.1f;

	this->_alive = true;
}

void Enemy::LoadTexture()
{
	_moveTextureID = GameRender::RegisterTexture(PathHelper::GetExePath() + ENEMY_MOVE_ANIMATION_TEXTURE_PATH);
	_moveAnimation.SetTextureID(_moveTextureID);

	_explosionTextureID = GameRender::RegisterTexture(PathHelper::GetExePath() + ENEMY_EXPLOSION_ANIMATION_TEXTURE_PATH);
	_explosionAnimation.SetTextureID(_explosionTextureID);
}

void Enemy::Initialize()
{
	this->_currentAnimation = _moveAnimation;
}

void Enemy::Update(GameWorld& world, sf::Time elapsed)
{
	if (_currentAnimation.IsDone() && _currentAnimation.IsRepeated())
	{
		_timeAnimation = 0;
		_currentAnimation.SetDone(false);
	}

	if (this->_life <= 0)
	{
		if (_currentAnimation.GetTexture() != _explosionAnimation.GetTexture())
		{
			_timeAnimation = 0;
			_currentAnimation = _explosionAnimation;
			_currentAnimation.ResetTime(0);
		}
		else if (_currentAnimation.IsDone())
		{
			this->_alive = false;
		}
	}

	_timeAnimation += elapsed.asMilliseconds();

	float speedFPS = elapsed.asMilliseconds() * this->_speed;
}

void Enemy::Draw(sf::RenderWindow* window, sf::Time elapsed)
{
	if (GameRender::IsVisible(this))
	{
		sf::Vector2f spriteSize = _currentAnimation.GetSpriteSize();
		sf::Vector2f spriteCenter = _currentAnimation.GetSpriteCenter();

		GraphicsUtils::InitQuad(_vertexArray, sf::Vector2f(spriteSize.x, spriteSize.y), sf::Vector2f(spriteCenter.x, spriteCenter.y), 0.25);
		GraphicsUtils::Transform(_vertexArray, sf::Vector2f(m_coord.x, m_coord.y), _angle);

		_currentAnimation.ApplyOnQuad(_vertexArray, _timeAnimation * 0.001);

		GameRender::AddQuad(_currentAnimation.GetTexture(), _vertexArray, RenderLayer::RENDER);
	}
}


void Enemy::Collision(WorldEntity* entity, GameWorld* gameWorld)
{
	if (this->_life > 0)
	{
		if (entity->GetType() == EntityTypes::BULLET)
		{
			std::cout << "hit" << std::endl;
			entity->Kill(gameWorld);
			this->_life -= 10;
		}
	}
}


void Enemy::SetBodyID(size_t id)
{
	this->_bodyID = id;
}

