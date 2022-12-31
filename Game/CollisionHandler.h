#pragma once
#include "Entity.h"
#include <iostream>

bool isCollision(const sf::FloatRect&, const sf::FloatRect&);
void processCollision(Entity& object1, Entity& object2);