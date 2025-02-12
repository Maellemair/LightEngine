#include "PVZScene.h"

#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"

#include "Debug.h"

#include <iostream>

void PVZScene::OnInitialize()
{
	Plant* mEntity1 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity1->Start(120, 10, 10.f, 20.f);

	Plant* mEntity2 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity2->Start(360, 10, 10.f, 20.f);

	Plant* mEntity3 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity3->Start(600, 10, 10.f, 20.f);

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

void PVZScene::TrySetSelectedEntity(Plant* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	mEntitySelected = pEntity;
}

void PVZScene::OnUpdate()
{
	for (int i = 0; i < mZombies.size(); i++)
	{
		for (int j = 0; j < mPlants.size(); j++)
		{
			if (mZombies[i]->GetPosition().y == mPlants[j]->GetPosition().y)
			{
				mPlants[j]->Update(mZombies[i]);
			}
			mPlants[j]->Update(nullptr);
		}
	}

	if (mEntitySelected != nullptr)
	{
		sf::Vector2f position = mEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	Debug::DrawLine(0, 240, 1280, 240, sf::Color(255, 255, 255, 120));
	Debug::DrawLine(0, 480, 1280, 480, sf::Color(255, 255, 255, 120));

	for (int i = 0; i < mPlants.size(); i++)
	{
		Debug::DrawText(10, mPlants[i]->GetPosition().y + 90,
			std::to_string(mPlants[i]->GetCharger().x) + " /" + std::to_string(mPlants[i]->GetCharger().y),
			sf::Color::Magenta);		
	}
}