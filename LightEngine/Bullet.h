#pragma once
#include "Entity.h"
#include <iostream>

class Zombie;

class Bullet : public Entity
{
	Entity* mTarget;
public:
	void Start(Entity* pEntity, Entity* target);
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
};	

