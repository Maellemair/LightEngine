#pragma once

#include "Entity.h"
#include "Gun.h"

class Bullet;

class Plant : public Entity
{

	Gun* Gatling;
public:
	void Start(float posY);
	void OnUpdate() override { Gatling->Update(GetDeltaTime()); }
	void AddBullet(Scene* pScene);
	void Reload() { Gatling->Reload(); }
};
	


