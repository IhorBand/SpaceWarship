#pragma once

#include "SFML/Graphics.hpp"

#include "Animation.h"
#include "GameRender.h"
#include "GraphicsUtils.h"
#include "PathHelper.h"

class Player : public WorldEntity
{
public:
	Player();
	Player(sf::Vector2f position);

	static void LoadTexture();
	void Initialize();
	void Update(GameWorld& world, sf::Time elapsed);
	void Draw(sf::RenderWindow* window, sf::Time elapsed);

	void SetBodyID(size_t id);

private:
	static uint64_t  _moveTextureID;
	static Animation _moveAnimation;

	size_t _bodyID;

	Animation _currentAnimation;
	float _timeAnimation = 0;

	float _speed = 0;
	float _life;
	
	bool _isReadyToShoot = true;
	float _timeShootCounter = 0;
	float _shootCooldown = 0.07f;
};