#include "CollisionHandler.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "HeroBullet.h"
#include "SimpleEnemyBullet.h"
#include "Hero.h"
#include "SimpleEnemy.h"
#include "SmartEnemy.h"
#include "StarBulletPowerUp.h"
#include "ExtraLife.h"
#include "StarBullet.h"
#include "ShieldPowerUp.h"
#include "BossEnemy.h"

namespace { // unnamed namespace — the standard way to make function "static"

			// primary collision-processing functions

	void heroBullet(Entity& spaceShip, Entity& bullet)
	{
		bullet.setAliveOrDead(false);
		Hero& ship = dynamic_cast<Hero&>(spaceShip);
		Bullet& bul = dynamic_cast<Bullet&>(bullet);
		ship.setHealth(bul.getDamage());
	}

	void heroEnemy(Entity& hero, Entity& enemy) {}
		

	void SimpleenemyBullet(Entity& enemy, Entity& bullet)
	{
		Enemy& e = dynamic_cast<Enemy&>(enemy);
		Bullet& b = dynamic_cast<Bullet&>(bullet);
		e.setHealthToEnemy(b.getDamage());
		bullet.setAliveOrDead(false);
	
	}

	void SmartenemyBullet(Entity& enemy, Entity& bullet)
	{
		Enemy& e = dynamic_cast<Enemy&>(enemy);
		Bullet& b = dynamic_cast<Bullet&>(bullet);
		e.setHealthToEnemy(b.getDamage());
		bullet.setAliveOrDead(false);
	}

	void heroPowerUp(Entity& h, Entity& powerup)
	{
		Hero& hero = dynamic_cast<Hero&>(h);
		PowerUp& pUp = dynamic_cast<PowerUp&>(powerup);
		hero.addScore(pUp.getScore());
		powerup.setAliveOrDead(false);
		sf::Time newTime(sf::seconds(0.17f));
		hero.setShootTime(newTime);
		hero.setBullet(WAVE_BULLET_STRING);
		Resources::get_instance().play(MUSIC_ID::POWER_UP_M);
	}

	void enemyWaveBullet(Entity& enemy, Entity& wave)
	{
		Enemy& e = dynamic_cast<Enemy&>(enemy);
		Bullet& b = dynamic_cast<Bullet&>(wave);
		e.setHealthToEnemy(b.getDamage());
	}

	void heroExtraLife(Entity& h, Entity& extralife)
	{
		Hero& e = dynamic_cast<Hero&>(h);
		PowerUp& b = dynamic_cast<PowerUp&>(extralife);
		e.addLife();
		e.addScore(b.getScore());
		extralife.setAliveOrDead(false);
		Resources::get_instance().play(MUSIC_ID::POWER_UP_M);
	}

	void shieldHero(Entity& shield, Entity& h)
	{
		Hero& e = dynamic_cast<Hero&>(h);
		PowerUp& b = dynamic_cast<PowerUp&>(shield);
		shield.setAliveOrDead(false);
		e.addScore(b.getScore());
		Resources::get_instance().play(MUSIC_ID::POWER_UP_M);
		e.setShield(true);
	}

	void BulletBoss(Entity& bullet, Entity& boss)
	{
		bullet.setAliveOrDead(false);
		Bullet& bull = dynamic_cast<Bullet&>(bullet);
		Enemy& b = dynamic_cast<Enemy&>(boss);
		b.setHealthToEnemy(bull.getDamage());
	}

	void StarBulletBoss(Entity& bullet, Entity& boss)
	{
		bullet.setAliveOrDead(false);
		Bullet& bull = dynamic_cast<Bullet&>(bullet);
		Enemy& b = dynamic_cast<Enemy&>(boss);
		b.setHealthToEnemy(bull.getDamage());
	}

	void bulletShip(Entity& bullet, Entity& h)
	{
		heroBullet(h, bullet);
	}

	void enemyHero(Entity& enemy, Entity& h)
	{
		heroEnemy(h, enemy);
	}

	void BulletSimpleEnemy(Entity& h, Entity& simpleEnemy)
	{
		SimpleenemyBullet(simpleEnemy, h);
	}

	void BulletSmartenemy(Entity& h, Entity& smartEnemy)
	{
		SmartenemyBullet(smartEnemy, h);
	}

	void powerupHero(Entity& powerup, Entity& h)
	{
		heroPowerUp(h, powerup);
	}

	void waveBulletEnemy(Entity& wave, Entity& enemy)
	{
		enemyWaveBullet(enemy, wave);
	}

	void extraLifeShip(Entity& extraLife, Entity& h)
	{
		heroExtraLife(h, extraLife);
	}

	void HeroShield(Entity& shield, Entity& h)
	{
		shieldHero(h, shield);
	}

	void bossBullet(Entity& boss, Entity& bullet)
	{
		BulletBoss(bullet, boss);
	}

	void bossWaveBullet(Entity& boss, Entity& bullet)
	{
		StarBulletBoss(bullet, boss);
	}

	using HitFunctionPtr = void(*)(Entity&, Entity&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Hero), typeid(SimpleEnemyBullet))] = &heroBullet;
		phm[Key(typeid(SimpleEnemyBullet), typeid(Hero))] = &bulletShip;
		phm[Key(typeid(Hero), typeid(SimpleEnemy))] = &heroEnemy;
		phm[Key(typeid(SimpleEnemy), typeid(Hero))] = &enemyHero;
		phm[Key(typeid(HeroBullet), typeid(SimpleEnemy))] = &BulletSimpleEnemy;
		phm[Key(typeid(SimpleEnemy), typeid(HeroBullet))] = &SimpleenemyBullet;
		phm[Key(typeid(SmartEnemy), typeid(HeroBullet))] = &SmartenemyBullet;
		phm[Key(typeid(HeroBullet), typeid(SmartEnemy))] = &BulletSmartenemy;
		phm[Key(typeid(Hero), typeid(StarBulletPowerUp))] = &heroPowerUp;
		phm[Key(typeid(StarBulletPowerUp), typeid(Hero))] = &powerupHero;
		phm[Key(typeid(StarBullet), typeid(SimpleEnemy))] = &waveBulletEnemy;
		phm[Key(typeid(SimpleEnemy), typeid(StarBullet))] = &enemyWaveBullet;
		phm[Key(typeid(StarBullet), typeid(SmartEnemy))] = &waveBulletEnemy;
		phm[Key(typeid(SmartEnemy), typeid(StarBullet))] = &enemyWaveBullet;
		phm[Key(typeid(Hero), typeid(ExtraLife))] = &heroExtraLife;  
		phm[Key(typeid(ExtraLife), typeid(Hero))] = &extraLifeShip;  
		phm[Key(typeid(Hero), typeid(ShieldPowerUp))] = &HeroShield;  
		phm[Key(typeid(ShieldPowerUp), typeid(Hero))] = &shieldHero; 
		phm[Key(typeid(HeroBullet), typeid(BossEnemy))] = &BulletBoss; 
		phm[Key(typeid(StarBullet), typeid(BossEnemy))] = &StarBulletBoss;

		return phm;
	}

	//looks up a map value by the keys
	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

//sends to correct collsion function 
void processCollision(Entity& object1, Entity& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	phf(object1, object2);
}

//checks to objects if thee was collision
bool isCollision(const sf::FloatRect& obj1, const sf::FloatRect&obj2)
{
	return obj1.intersects(obj2);
}