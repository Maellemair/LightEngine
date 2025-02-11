#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	void Start(Entity* pEntity);
	void Update();
	void OnCollision(Entity* other) override;
};

