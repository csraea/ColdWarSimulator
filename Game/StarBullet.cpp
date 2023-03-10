#include "StarBullet.h"
#include "BulletFactory.h"
#include "Resources.h"

//-----------------------------------------------------------------------------
StarBullet::StarBullet(const bullet_pkg& pkg)
{
	m_Sprite.setPosition(pkg.initialPos);
	m_heroBullet = pkg.heroBullet;
	m_direction = pkg.driection;
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(TEXTURES::STAR_BULLET_T));;
	m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));
	m_damage = -5;
}
//-----------------------------------------------------------------------------
void StarBullet::move(sf::Vector2f)
{
	if (m_Sprite.getPosition().x + m_Sprite.getTexture()->getSize().x / 2 +
		m_direction.x >= WINDOW_SIZE.x ||
		m_Sprite.getPosition().x - m_Sprite.getTexture()->getSize().x / 2 + m_direction.x <= 0 ||
		m_Sprite.getPosition().y <= 0 || m_Sprite.getPosition().y >= WINDOW_SIZE.y)
		isAlive = false;

	m_Sprite.move(m_direction.x * 4, m_direction.y * 4);
	m_Sprite.rotate(-5);
}
//-----------------------------------------------------------------------------
bool StarBullet::m_registerit = BulletFactory::registerit(WAVE_BULLET_STRING,
	[](const bullet_pkg& x) -> std::unique_ptr<Bullet> { return std::make_unique<StarBullet>(x); });