#pragma once
#include "Bullet.h"

class BulletFactory;

class HeroBullet : public Bullet
{
public:
	HeroBullet(const bullet_pkg&);
	~HeroBullet() = default;
	void move(sf::Vector2f = { 0.f, 0.f }) override;

private:
	static bool m_registerit;
};