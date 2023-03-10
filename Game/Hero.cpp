#include "Hero.h"
#include "Resources.h"
#include "BulletFactory.h"

//-----------------------------------------------------------------------------
Hero::Hero(sf::Vector2f start_pos) : m_life(3), m_health(100)
{
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::HERO_T));
	m_Sprite.setPosition(start_pos);
	m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));

	m_bulletFactory_ptr = std::make_shared < BulletFactory>();
	m_bullet_string = DEFAULT_HERO_BULLET_STRING;
}
//-----------------------------------------------------------------------------
void Hero::move(sf::Vector2f offset)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(m_shielded)
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::SHIELD_HERO_LEFT_T));
		else
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::HERO_LEFT_T));
		offset = { -3.f, 0.f };
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_shielded)
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::SHIELD_HERO_RIGHT_T));
		else
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::HERO_RIGHT_T));
		offset = { 3.f, 0.f };
	}
	else
	{
		if (m_shielded)
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::SHIELD_HERO_T));
		else 
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::HERO_T));
	}
		
	if (m_Sprite.getPosition().x + m_Sprite.getTexture()->getSize().x / 2 +
		offset.x >= WINDOW_SIZE.x ||
		m_Sprite.getPosition().x - m_Sprite.getTexture()->getSize().x / 2 + offset.x <= 0)
		return;

	m_Sprite.move(offset);

	if (m_Sprite.getTextureRect().top < 0)
		return;
}
//-----------------------------------------------------------------------------
std::unique_ptr<Bullet> Hero::shoot() const
{
	Resources::get_instance().play(MUSIC_ID::SHOOT_M);
	struct bullet_pkg shipBullet;
	shipBullet.initialPos = { m_Sprite.getPosition().x  ,m_Sprite.getPosition().y - m_Sprite.getGlobalBounds().height / 2 };
	shipBullet.heroBullet = true;
	shipBullet.driection = { 0,-1 };
	shipBullet.damage = -25; 

	return m_bulletFactory_ptr->create(m_bullet_string, shipBullet);
}
//-----------------------------------------------------------------------------
float Hero::getHealth()
{
	return m_health;
}
//-----------------------------------------------------------------------------
void Hero::setHealth(float health)
{
	if(!m_shielded)
		m_health += health;

	if (m_health <= 0)
	{
		m_life--;
		m_health = MAX_HEALTH;
	}	
}
//-----------------------------------------------------------------------------
int Hero::getLife()
{
	return m_life;
}
//-----------------------------------------------------------------------------
void Hero::draw(sf::RenderWindow &window)
{
	if (m_shielded)
	{
		auto p = m_Sprite.getTextureRect();
		p.width = Resources::get_instance().getGeneralTexture(TEXTURES::SHIELD_HERO_RIGHT_T).getSize().x;
		p.height = Resources::get_instance().getGeneralTexture(TEXTURES::SHIELD_HERO_RIGHT_T).getSize().y;
		m_Sprite.setTextureRect(p);
		m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));

		
		const static sf::Time shieldTime = sf::seconds(20.f);
		static bool resetClock = false;

		if (shieldClock.getElapsedTime() > shieldTime)  
		{
			m_shielded = false;
			resetClock = true;
		}

		if (resetClock)
		{
			shieldClock.restart();
			resetClock = false;
		}
	}
	else
	{
		auto p = m_Sprite.getTextureRect();
		p.width = Resources::get_instance().getGeneralTexture(TEXTURES::HERO_T).getSize().x;
		p.height = Resources::get_instance().getGeneralTexture(TEXTURES::HERO_T).getSize().y;
		m_Sprite.setTextureRect(p);
		m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));
	}

	window.draw(m_Sprite);
}
//-----------------------------------------------------------------------------
void Hero::addScore(unsigned score) 
{
	m_score += score;
}