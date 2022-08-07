#include "Bullet.h"

Animation Bullet::_moveAnimation(1, 1, 121, 126, 1, 1);

Bullet::Bullet() :
	StandardEntity()
{

}

Bullet::Bullet(const sf::Vector2f& coord) :
	StandardEntity(coord.x, coord.y, 0)
{
	this->_type = EntityTypes::BULLET;

	this->_speed = 0.3f;
	this->_alive = true;
}

void Bullet::LoadTexture()
{
	size_t textureID = GameRender::RegisterTexture(PathHelper::GetExePath() + BULLET_TEXTURE_PATH);
	_moveAnimation.SetTextureID(textureID);
}

void Bullet::Initialize()
{
}

void Bullet::Update(GameWorld& world, sf::Time elapsed)
{
	float speedFPS = elapsed.asMilliseconds() * this->_speed;

	m_coord.y += -speedFPS;

	if (this->m_coord.x < 0 || this->m_coord.x > MAP_SIZE_WIDTH || this->m_coord.y < 0 || this->m_coord.y > MAP_SIZE_HEIGHT)
	{
		this->_alive = false;
	}
}

void Bullet::Draw(sf::RenderWindow* window, sf::Time elapsed)
{
	if (GameRender::IsVisible(this))
	{
		sf::Vector2f spriteSize = _moveAnimation.GetSpriteSize();
		sf::Vector2f spriteCenter = _moveAnimation.GetSpriteCenter();

		GraphicsUtils::InitQuad(_vertexArray, sf::Vector2f(spriteSize.x, spriteSize.y), sf::Vector2f(spriteCenter.x, spriteCenter.y), 0.25);
		GraphicsUtils::Transform(_vertexArray, sf::Vector2f(m_coord.x, m_coord.y), _angle);

		_moveAnimation.ApplyOnQuad(_vertexArray, 0);

		GameRender::AddQuad(_moveAnimation.GetTexture(), _vertexArray, RenderLayer::BULLETS);
	}
}

void Bullet::Kill(GameWorld* world)
{
	//CollisionBody::GetObjectAt(static_cast<uint32_t>(this->_bulletBodyID))->Remove();

	this->_alive = false;

	//this->Remove();
}

void Bullet::SetBulletBodyID(size_t id)
{
	this->_bulletBodyID = id;
}

bool Bullet::IsAlive()
{
	return this->_alive;
}
