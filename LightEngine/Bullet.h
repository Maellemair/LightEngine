#pragma once
#include "Entity.h"
#include <iostream>

class Bullet : public Entity
{
public:
	void Start(Entity* pEntity);
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
};	

