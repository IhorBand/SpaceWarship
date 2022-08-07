#pragma once

#include "SFML/Graphics.hpp"

#include "Animation.h"
#include "GameRender.h"
#include "GraphicsUtils.h"
#include "PathHelper.h"
#include "SoundManager.h"

class Enemy : public WorldEntity
{
public:
	Enemy();
	Enemy(sf::Vector2f position);

	static void LoadTexture();
	void Initialize();
	void Update(GameWorld& world, sf::Time elapsed);
	void Draw(sf::RenderWindow* window, sf::Time elapsed);

	void Collision(WorldEntity* entity, GameWorld* gameWorld);

	void SetBodyID(size_t id);

private:
	static uint64_t  _moveTextureID;
	static Animation _moveAnimation;
	static uint64_t _explosionTextureID;
	static Animation _explosionAnimation;
	static size_t _explosionSoundID;

	size_t _bodyID;

	Animation _currentAnimation;
	float _timeAnimation = 0;

	float _speed = 0;
	float _life;

	bool _isReadyToShoot = true;
	float _timeShootCounter = 0;
	float _shootCooldown = 0.07f;

	bool _isExplosionStarted = false;
};