// hotfix to prevent failures between SFML and windows.h
#define NOMINMAX

#include "Game.h"

#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "SoundManager.h"

Game* Game::s_instance = nullptr;
size_t Game::_backgroundSoundID;

Game::Game()
{

}

Game* Game::GetInstance()
{
	if (!Game::s_instance)
	{
		Game::s_instance = new Game();
	}

	return Game::s_instance;
}

int Game::LoadConfigurationFile()
{
	CSimpleIniA iniFile;
	iniFile.SetUnicode();
	SI_Error rc = iniFile.LoadFile(PathHelper::GetConfigurationPath().c_str());
	if (rc < 0)
	{
		std::cout << "Cannot open configuration file. " << std::endl;
		return -1;
	}

	const char* buffer;
	
	buffer = iniFile.GetValue(ConfigurationSection::Window, ConfigurationProperty::ResolutionWidth);
	Game::s_instance->resolutionWidth = atoi(buffer);
	
	buffer = iniFile.GetValue(ConfigurationSection::Window, ConfigurationProperty::ResolutionHeight);
	Game::s_instance->resolutionHeight = atoi(buffer);

	return 0;
}

int Game::LoadTextures()
{
	Game::s_instance->world.Initialize();

	Bullet::LoadTexture();
	Player::LoadTexture();
	Enemy::LoadTexture();

	_backgroundSoundID = SoundManager::RegisterSound(PathHelper::GetExePath() + BACKGROUND_MUSIC_PATH);

	return 0;
}

int Game::LoadEntities()
{
	
	Player* player = new Player(sf::Vector2f(300, 500));
	Game::s_instance->world.AddEntity(player);

	CollisionBody* collisionPlayerBodyPtr = new CollisionBody();
	collisionPlayerBodyPtr->setEntity(player);
	player->SetBodyID(Game::s_instance->world.AddPhysicEntity(collisionPlayerBodyPtr));

	// just for test :)
	int x = 1;
	int y = 1;
	for (int i = 1; i <= 12; i++)
	{
		Enemy* enemy = new Enemy(sf::Vector2f(100 * x, 100 * y));
		Game::s_instance->world.AddEntity(enemy);

		CollisionBody* collisionEnemyBodyPtr = new CollisionBody();
		collisionEnemyBodyPtr->setEntity(enemy);
		enemy->SetBodyID(Game::s_instance->world.AddPhysicEntity(collisionEnemyBodyPtr));

		x++;
		if (x > 4)
		{
			x = 1;
			y++;
		}
	}

	return 0;
}

int Game::Initialize()
{
	if (Game::LoadConfigurationFile() < 0)
	{
		std::cout << "Cannot load configuration file. " << std::endl;
		return -1;
	}

	std::cout << "Resolution: " << Game::s_instance->resolutionWidth << "x" << Game::s_instance->resolutionHeight << std::endl;

	Game::s_instance->renderWindow = new sf::RenderWindow(sf::VideoMode(Game::s_instance->resolutionWidth, Game::s_instance->resolutionHeight), Game::s_instance->gameName);
	Game::s_instance->renderWindow->setTitle(Game::s_instance->gameName);
	Game::s_instance->renderWindow->setMouseCursorVisible(false);
	Game::s_instance->renderWindow->setFramerateLimit(60);

	GameRender::Initialize(Game::s_instance->resolutionWidth, Game::s_instance->resolutionHeight);

	Game::LoadTextures();

	Game::LoadEntities();

	SoundManager::PlayInstanceOf(_backgroundSoundID, 30, true);

	return 0;
}

void Game::ProcessEvents()
{
	while (Game::s_instance->renderWindow->pollEvent(Game::s_instance->event))
	{		
		if (Game::s_instance->event.type == sf::Event::Closed
			|| (Game::s_instance->event.type == sf::Event::KeyPressed && Game::s_instance->event.key.code == sf::Keyboard::Key::Escape))
			Game::s_instance->renderWindow->close();
	}
}

void Game::Update(sf::Time elapsed)
{
	Game::s_instance->world.Update(elapsed);
	
	//GameRender::setFocus({ p.x, p.y });

	//Game::s_instance->renderWindow->clear();
	GameRender::Clear();

	Game::s_instance->world.Draw(Game::s_instance->renderWindow, elapsed);

	GameRender::Display(Game::s_instance->renderWindow);
	Game::s_instance->renderWindow->display();
}

void Game::Start()
{
	Game::s_instance = Game::GetInstance();

	if (Game::Initialize() < 0)
	{
		std::cout << "Initialization error occured." << std::endl;
		return;
	}

	while (Game::s_instance->renderWindow->isOpen())
	{
		sf::Time elapsed = Game::s_instance->clock.restart();
		Game::s_instance->ProcessEvents();
		Game::s_instance->Update(elapsed);
	}
}