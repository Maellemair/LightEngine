#include "Zombie.h"
#include "PVZScene.h"

#include <iostream>

void Zombie::Start(float posY)
{
	if (posY < 230)
	{
		SetPosition(1330, 120);
	}
	else if (posY < 480)
	{
		SetPosition(1330, 360);
	}
	else
	{
		SetPosition(1330, 600);
	}
	SetRigidBody(false);
	SetDirection(-1, 0, 200);
	SetTag((int)PVZScene::Tag::Zombie);
}

void Zombie::OnUpdate()
{
	if (GetPosition().x + 50 <= 0)
	{
		this->Destroy();
	}
}
