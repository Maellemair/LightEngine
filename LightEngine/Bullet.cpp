#include "Bullet.h"
#include "PVZScene.h"
#include "Zombie.h"

#include <iostream>

void Bullet::Start(Entity* pEntity, Entity* target)
{
	SetPosition(pEntity->GetPosition().x, pEntity->GetPosition().y);
	SetTag((int)PVZScene::Tag::Bullet);
	if (target != nullptr)
	{
		SetDirection(target->GetPosition().x, target->GetPosition().y, 500);
		mTarget = target;
	}
	else
	{
		SetDirection(1, 0, 500);
		mTarget = nullptr;
	}
}

void Bullet::OnUpdate()
{
	if (mTarget != nullptr)
	{
		SetDirection(mTarget->GetPosition().x, mTarget->GetPosition().y, 500);
	}
	if (GetPosition().x - 10 >= GameManager::Get()->GetWindowWidth())
	{
		this->Destroy();
	}
}

void Bullet::OnCollision(Entity* other)
{
	if(other->IsTag((int)PVZScene::Tag::Zombie))
	{
		other->Destroy();
		this->Destroy();
		std::cout << "Hit" << std::endl;
	}
}
