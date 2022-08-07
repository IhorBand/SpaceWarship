#include "Player.h"

#include "Bullet.h"
#include "GameWorld.h"
#include "SoundManager.h"

uint64_t Player::_moveTextureID;
Animation Player::_moveAnimation(8, 1, 512, 512, 8, 15);
size_t Player::_shootSoundID;

Player::Player() : WorldEntity(sf::Vector2f(300,200), sf::VertexArray(sf::Quads, 4), 0)
{
	this->_life = 100;
	this->_type = EntityTypes::PLAYER;

	this->_speed = 0.1f;

	this->_alive = true;
}

Player::Player(sf::Vector2f position) : WorldEntity(position, sf::VertexArray(sf::Quads, 4), 0)
{
	this->_life = 100;
	this->_type = EntityTypes::PLAYER;

	this->_speed = 0.1f;

	this->_alive = true;
}

void Player::LoadTexture()
{
	_moveTextureID = GameRender::RegisterTexture(PathHelper::GetExePath() + PLAYER_MOVE_ANIMATION_TEXTURE_PATH);
	_moveAnimation.SetTextureID(_moveTextureID);

	_shootSoundID = SoundManager::RegisterSound(PathHelper::GetExePath() + PLAYER_SHOOT_SOUND_PATH, 100);
}

void Player::Initialize()
{
	this->_currentAnimation = _moveAnimation;
}

void Player::Update(GameWorld& world, sf::Time elapsed)
{
	if (_currentAnimation.IsDone())
	{
		_timeAnimation = 0;
		_currentAnimation.SetDone(false);
	}

	_timeAnimation += elapsed.asMilliseconds();

	if (_isReadyToShoot == false)
	{
		_timeShootCounter += elapsed.asSeconds();
		if (_timeShootCounter >= _shootCooldown)
		{
			_isReadyToShoot = true;
			_timeShootCounter = 0;
		}
	}

	float speedFPS = elapsed.asMilliseconds() * this->_speed;

	float vx = 0;
	float vy = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		vx = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		vx = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		vy = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		vy = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && _isReadyToShoot)
	{
		Bullet* bulletPtr(Bullet::NewEntity(sf::Vector2f(m_coord.x, m_coord.y)));
		world.AddEntity(bulletPtr);

		CollisionBody* collisionBodyPtr = CollisionBody::Add();
		collisionBodyPtr->setEntity(bulletPtr);
		bulletPtr->SetBulletBodyID(world.AddPhysicEntity(collisionBodyPtr));

		SoundManager::PlayInstanceOf(_shootSoundID, 10);

		_isReadyToShoot = false;
	}

	m_coord.x += vx * speedFPS;
	m_coord.y += vy * speedFPS;

	if (this->_life < 0)
	{
		this->_alive = false;
	}
}

void Player::Draw(sf::RenderWindow* window, sf::Time elapsed)
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

void Player::SetBodyID(size_t id)
{
	this->_bodyID = id;
}

