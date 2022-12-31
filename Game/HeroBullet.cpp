#include "HeroBullet.h"
#include "BulletFactory.h"
#include "Resources.h"

//-----------------------------------------------------------------------------
HeroBullet::HeroBullet(const bullet_pkg& pkg)
{
	m_Sprite.setPosition(pkg.initialPos);
	m_heroBullet = pkg.heroBullet;
	m_direction = pkg.driection;
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::HERO_BULLET_T));;
	m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));
	m_damage = pkg.damage;
}
//-----------------------------------------------------------------------------
void HeroBullet::move(sf::Vector2f )
{
	m_Sprite.move(m_direction.x*4, m_direction.y * 4);
	m_Sprite.rotate(1.2f);
}
//-----------------------------------------------------------------------------
bool HeroBullet::m_registerit = BulletFactory::registerit(DEFAULT_HERO_BULLET_STRING,  
	[](const bullet_pkg& x) -> std::unique_ptr<Bullet> { return std::make_unique<HeroBullet>(x); });