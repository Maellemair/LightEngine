#pragma once

#include "Scene.h"

class Plant;
class Zombie;
class Bullet;

class PVZScene : public Scene
{
	Plant* mEntity1;
	Plant* mEntity2;
	Plant* mEntity3;

	std::vector<Zombie*> mZombies;

	Plant* mEntitySelected;

private:
	void TrySetSelectedEntity(Plant* pEntity, int x, int y);

public:
	enum class Tag
	{
		Plant,
		Zombie,
		Bullet
	};
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};





