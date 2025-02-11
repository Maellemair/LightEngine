#pragma once

#include "Entity.h"

class Bullet;

class Plant : public Entity
{
public:
	void Start(float posY);
	void AddBullet(Scene* pScene);
};

