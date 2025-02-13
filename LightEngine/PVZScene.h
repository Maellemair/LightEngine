#pragma once

#include "Scene.h"

class Plant;
class Zombie;
class Bullet;

class PVZScene : public Scene
{
	std::vector<Zombie*> mZombies;
	std::vector<Plant*> mPlants;
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
	bool CheckIfZombieOnLane(Plant* pPlant);
	Zombie* CheckZombieClose(Plant* pEntity);
	void OnUpdate() override;

	template <typename T>
	void Clear(std::vector<T>& vector);
};

template<typename T>
void PVZScene::Clear(std::vector<T>& vector)
{
	for (auto it = vector.begin(); it != vector.end(); )
	{
		T entity = *it;

		if (entity->ToDestroy() == false)
		{
			++it;
			continue;
		}
		it = vector.erase(it);
	}
}
