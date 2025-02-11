#include "PVZScene.h"

#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"

#include "Debug.h"

void PVZScene::OnInitialize()
{
	mEntity1 = CreateEntity<Plant>(50, sf::Color::Green);
	mEntity1->SetPosition(100, 100);
	mEntity1->SetRigidBody(true);

	mEntity2 = CreateEntity<Zombie>(50, sf::Color::Red);
	mEntity2->SetPosition(500, 500);
	mEntity2->SetRigidBody(true);

	mEntitySelected = nullptr;
}

void PVZScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(mEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(mEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (mEntitySelected != nullptr)
		{
			mEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
}

void PVZScene::TrySetSelectedEntity(Entity* pEntity, int x, int y)
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
}