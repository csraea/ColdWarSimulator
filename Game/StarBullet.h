#pragma once
#include "Bullet.h"

class BulletFactory;

class StarBullet : public Bullet
{
public:
	StarBullet(const bullet_pkg& pkg);
	~StarBullet() = default;;
	void move(sf::Vector2f = { 0.f, 0.f }) override;

private:
	static bool m_registerit;
};