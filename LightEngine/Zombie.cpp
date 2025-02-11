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
	SetRigidBody(true);
	SetDirection(-1, 0, 100);
	SetTag((int)PVZScene::Tag::Zombie);
}
