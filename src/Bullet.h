#pragma once

#include "SFML/Graphics.hpp"

#include "Animation.h"
#include "GameRender.h"
#include "GraphicsUtils.h"
#include "PathHelper.h"
#include "StandardEntity.h"

class Bullet : public StandardEntity<Bullet>
{
public:
	Bullet();
	Bullet(const sf::Vector2f& coord);

	static void LoadTexture();
	void Initialize();
	void Update(GameWorld& world, sf::Time elapsed);
	void Draw(sf::RenderWindow* window, sf::Time elapsed);
	void Kill(GameWorld* world);

	void SetBulletBodyID(size_t id);

	bool IsAlive();

private:
	static Animation _moveAnimation;

	size_t _bulletBodyID;

	float _speed = 0;
};