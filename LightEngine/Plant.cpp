#include "Plant.h"
#include "Bullet.h"
#include "PVZScene.h"

void Plant::Start(float posY)
{
	Gatling = new Gun(10);
	SetPosition(70, posY);
	SetRigidBody(true); 
	SetTag((int)PVZScene::Tag::Plant);
}

void Plant::AddBullet(Scene* pScene)
{
	if(Gatling->Shoot())
	{
		Bullet* bullet = pScene->CreateEntity<Bullet>(10, sf::Color::White);
		bullet->Start(this);
	}
}
