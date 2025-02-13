#include "PVZScene.h"

#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"

#include "Debug.h"
#include "Utils.h"

#include <iostream>

void PVZScene::OnInitialize()
{
	Plant* mEntity1 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity1->Start(120, 10, 1.f, 3.5f);

	Plant* mEntity2 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity2->Start(360, 10, 1.f, 3.5f);

	Plant* mEntity3 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity3->Start(600, 10, 1.f, 3.5f);

	mPlants.push_back(mEntity1);
	mPlants.push_back(mEntity2);
	mPlants.push_back(mEntity3);

	mEntitySelected = nullptr;
}

void PVZScene::OnEvent(const sf::Event& event)
{
	if (event.type == sf::Event::EventType::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			Zombie* zombie = CreateEntity<Zombie>(50, sf::Color::Red);
			zombie->Start(event.mouseButton.y);
			mZombies.push_back(zombie);
		}
	}	
}

bool PVZScene::CheckIfZombieOnLane(Plant* pPlant)
{
	int NbrZombieOnLane = 0;
	for (Zombie* pEntity : mZombies)
	{
		if (pEntity->GetPosition().y == pPlant->GetPosition().y &&
			pEntity->GetPosition().x <= GetWindowWidth() / 2)
		{
			NbrZombieOnLane++;
		}
	}
	if (NbrZombieOnLane != 0)
	{
		return true;
	}
	return false;
}

Zombie* PVZScene::CheckZombieClose(Plant* pEntity)
{
	if (mZombies.size() == 0)
	{
		return nullptr;
	}

	Zombie* MostCloseZombie = nullptr;
	float ShortDistance = NULL;

	if(mZombies[0]->GetPosition().x <= GetWindowWidth() / 2)
	{
		MostCloseZombie = mZombies[0];
		ShortDistance = Utils::GetDistance(pEntity->GetPosition().x,
			pEntity->GetPosition().y,
			MostCloseZombie->GetPosition().x,
			MostCloseZombie->GetPosition().y);
	}

	for (Zombie* zombie : mZombies)
	{
		if(zombie->GetPosition().x <= GetWindowWidth() / 2)
		{
			float distance = Utils::GetDistance(pEntity->GetPosition().x,
				pEntity->GetPosition().y,
				zombie->GetPosition().x,
				zombie->GetPosition().y);

			if (distance < ShortDistance)
			{
				ShortDistance = distance;
				MostCloseZombie = zombie;
			}
		}
	}

	return MostCloseZombie;
}

void PVZScene::TrySetSelectedEntity(Plant* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	mEntitySelected = pEntity;
}

void PVZScene::OnUpdate()
{
	if (mEntitySelected != nullptr)
	{
		sf::Vector2f position = mEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	for (int i = 0; i < mPlants.size(); i++)
	{
		mPlants[i]->UpdateAction(GetDeltaTime());
	}

	Clear<Zombie*>(mZombies);
	Clear<Plant*>(mPlants);

	Debug::DrawLine(0, 240, 1280, 240, sf::Color(255, 255, 255, 120));
	Debug::DrawLine(0, 480, 1280, 480, sf::Color(255, 255, 255, 120));

	for (int i = 0; i < mPlants.size(); i++)
	{
		Debug::DrawText(10, mPlants[i]->GetPosition().y + 90,
			std::to_string(mPlants[i]->GetCharger().x) + " /" + std::to_string(mPlants[i]->GetCharger().y),
			sf::Color::Magenta);		
	}
}