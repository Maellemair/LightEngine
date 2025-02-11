#include "PVZScene.h"

#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"

#include "Debug.h"

#include <iostream>

void PVZScene::OnInitialize()
{
	mEntity1 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity1->Start(120);

	mEntity2 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity2->Start(360);

	mEntity3 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity3->Start(600);

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
		else if (event.mouseButton.button == sf::Mouse::Button::Right)
		{
			TrySetSelectedEntity(mEntity1, event.mouseButton.x, event.mouseButton.y);
			TrySetSelectedEntity(mEntity2, event.mouseButton.x, event.mouseButton.y);
			TrySetSelectedEntity(mEntity3, event.mouseButton.x, event.mouseButton.y);
		}
	}
	else if (event.type == sf::Event::EventType::KeyPressed)
	{
		if(mEntitySelected != nullptr)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				mEntitySelected->AddBullet(this);
			}
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
	if (mEntitySelected != nullptr)
	{
		sf::Vector2f position = mEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
	Debug::DrawLine(0, 240, 1280, 240, sf::Color(255, 255, 255, 120));
	Debug::DrawLine(0, 480, 1280, 480, sf::Color(255, 255, 255, 120));
}