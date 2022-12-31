#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <map>
#include <unordered_map>
#include "MyExceptions.h"
#include <algorithm>
#include <random>

enum ENEMY_CHARS
{
	SIMPLE_ENEMY_C = 'a',
	SMART_ENEMY_C = 'b',
	BOSS_ENEMY_C = 'f'
};
enum POWER_UP_CHARS
{
	EXTRA_LIFE_C = 'c',
	WAVE_BULLET_C = 'd',
	SHIELD_C = 'e',
};

static const std::string WAVE_BULLET_STRING = "wave bullet";
static const std::string SIMPLE_ENEMY_BULLET_STRING = "simple enemy bullet";
static const std::string DEFAULT_HERO_BULLET_STRING = "default bullet";
static const int MAX_LEVELS = 3; 
static const sf::Vector2f WINDOW_SIZE = { 1440.f, 900.f };  //size of window
static const float MAX_HEALTH = 100;

struct bullet_pkg
{
	sf::Vector2f initialPos;
	sf::Vector2f driection;
	bool heroBullet;
	float damage;
};

struct enemy_pkg
{
	sf::Vector2f initialPos;
	float yLimit;
};

struct powerUp_pkg
{
	sf::Vector2f initialPos;
	int velocity;
};

enum TEXTURES
{
	GAME_BACKGROUND_T = 0,
	GAMEOVER_BACKGROUND1_T,
	GAMEOVER_BACKGROUND2_T,
	MENU_BACKGROUND_T,

	START_BUTTON_T,
	EXIT_BUTTON_T,
	RESUME_BUTTON_T,

	HERO_T,
	HERO_LEFT_T,
	HERO_RIGHT_T,
	
	SHIELD_HERO_T,
	SHIELD_HERO_LEFT_T,
	SHIELD_HERO_RIGHT_T,

	ENEMY_BULLET_T,
	HERO_BULLET_T,
	STAR_BULLET_T,

	HEALTH_T,
	INNER_HEALTH_T,
	TELEPORTATION_T,
	DEATH_T,
	BONUS_T,

	DUMMY_ENEMY_T,
	CLEVER_ENEMY_T,
	BOSS_T,
	BOSS_LOWLIFE_T,

	MAIN_LOGO_T,
	MAX
};