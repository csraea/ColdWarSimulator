#pragma once
#include "Weaponable.h"

class Bullet;

class Hero : public Weaponable
{
public:
	Hero(sf::Vector2f);
	~Hero() = default;
	void move(sf::Vector2f = { 0.f, 0.f }) override;
	void setShootTime(sf::Time & newTime) { shootTime = newTime; }
	void setBullet(const std::string c) { m_bullet_string = c; }
	void addLife() { m_life++; }
	void setShield(bool shield) { m_shielded = shield; shieldClock.restart(); }
	void draw(sf::RenderWindow&) override;
	void setPosition(const sf::Vector2f &pos){} 
	void setHealth(float);

	void addScore(unsigned score); 
	int getLife();
	float getHealth();
	sf::Time getShootTime() { return shootTime; }
	std::unique_ptr<Bullet> shoot() const override;
private:
	std::string m_bullet_string;
	sf::Time shootTime = sf::seconds(0.35f);
	int m_life;
	float m_health;   
	bool m_shielded = false;
	sf::Clock shieldClock;
};