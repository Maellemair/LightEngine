#pragma once

#include "Scene.h"

class Plant;
class Zombie;
class Bullet;

class PVZScene : public Scene
{
	Plant* mEntity1;
	Zombie* mEntity2;

	std::vector<Bullet*> mBullets;

	Entity* mEntitySelected;

private:
	void TrySetSelectedEntity(Entity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};





