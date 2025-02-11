#include "Bullet.h"
#include "PVZScene.h"

#include <iostream>

void Bullet::Start(Entity* pEntity)
{
	SetPosition(pEntity->GetPosition().x, pEntity->GetPosition().y);
	SetTag((int)PVZScene::Tag::Bullet);
	SetDirection(1, 0, 50);
}

void Bullet::OnUpdate()
{
	if (GetPosition().x - 10 >= GameManager::Get()->GetWindowWidth())
	{
		this->Destroy();
	}
}

void Bullet::OnCollision(Entity* other)
{
	if(other->IsTag((int)PVZScene::Tag::Zombie))
	{
		std::cout << "Hit" << std::endl;
		other->Destroy();
		this->Destroy();
	}
}
