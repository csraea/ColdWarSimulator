#pragma once
#include "PowerUp.h"

class StarBulletPowerUp : public PowerUp
{
public:
	StarBulletPowerUp(const powerUp_pkg& x);
	~StarBulletPowerUp() = default;
private:
	static bool m_registerit;
};