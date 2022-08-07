#pragma once

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SimpleIni.h"

#include "PathHelper.h"
#include "ConfigurationSection.h"
#include "ConfigurationProperty.h"
#include "GameWorld.h"

class Game
{
public:
	static void Start();

private:
	Game();

	static Game* GetInstance();

	static Game* s_instance;

	static size_t _backgroundSoundID;

	static int LoadConfigurationFile();
	static int LoadTextures();
	static int LoadEntities();
	static int Initialize();
	static void ProcessEvents();
	static void Update(sf::Time elapsed);

	const std::string gameName = "Space Invaders";
	
	sf::RenderWindow* renderWindow = nullptr;
	sf::Clock clock;
	sf::Event event;
	GameWorld world;

	int resolutionWidth = 1280;
	int resolutionHeight = 720;

};