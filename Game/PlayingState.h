#pragma once
#include "EnemyFactory.h"
#include "LevelController.h"
#include "PowerUp.h"
#include "State.h"

class Hero;
class Enemy;
class Bullet;

class PlayingState : public State
{
public:
	PlayingState(std::shared_ptr<GameController> game);
	PlayingState() = default;
	~PlayingState() = default;

	void update(sf::RenderWindow&);
	void nextLevel();
	void updateHero( sf::Event&);
	void updateInnerHealthBar();
	void draw() override;
	void update()override;
	void handleInput() override;

private:
	void activateStart();
	void PauseGame(); 
	void moveAll();
	void enemyShoot();
	void teleportEnemy();
	void activatePowerUp();
	void collisions();
	void scrollBackground(sf::RenderWindow&);
	void gameOverScreen(int coef);

	std::unique_ptr<Hero> m_hero;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<Bullet>> m_bullets;
	std::vector<std::unique_ptr<PowerUp>> m_powerUps;
	std::vector<sf::Sprite> m_lives;

	//EnemyFactory m_factory;
	LevelController m_levelmanager;

	sf::Sprite m_gameBackground;
	sf::Sprite m_gameBackground2;
	sf::Sprite m_healthBar;
	sf::Sprite m_innerHealthBar;
	sf::Sprite m_heroSprite;
	sf::Text m_gameScore;
	sf::Text m_waveText;

	int m_teleported_enemy = -1;
	int m_level;
	const sf::Time moveTime = sf::seconds((float)0.008);
	const sf::Time shootTime = sf::seconds(0.5f);
	const sf::Time powerUpTime = sf::seconds(5.f);
	const sf::Time teleportTime = sf::seconds(0.2f);
	sf::Time updateTime = sf::seconds(0);
	sf::Time totalShootTime = sf::seconds(0.f);
	sf::Time totalpowerUpTime = sf::seconds(0.f);
	sf::Time TOD = sf::seconds(0.f);
	sf::Clock shoot_clock;
};