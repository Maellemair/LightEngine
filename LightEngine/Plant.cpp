#include "Plant.h"
#include "Bullet.h"
#include "Zombie.h"
#include "PVZScene.h"
#include "Actions.h"
#include "Debug.h"

void Plant::Start(float posY, int capacity, float shootTime, float reloadTime)
{
	SetPosition(70, posY);
	SetRigidBody(true); 
	SetTag((int)PVZScene::Tag::Plant);

	mAmmo = capacity;
	mCapacity = capacity;

	mActions[(int)State::Full] = new ActionFull();
	mActions[(int)State::Idle] = new ActionIdle();
	mActions[(int)State::Loaded] = new ActionLoaded();
	mActions[(int)State::Shooting] = new ActionShoot(shootTime);
	mActions[(int)State::Empty] = new ActionEmpty();
	mActions[(int)State::Reloading] = new ActionReload(reloadTime);

	TransitionTo(State::Idle);
}

void Plant::OnUpdate()
{
	PVZScene* scene = GetScene<PVZScene>();
	if (scene->CheckIfZombieOnLane(this) == 0)
	{
		if (Reload() && mAmmo <= mCapacity / 2)
		{
			std::cout << "Reload" << std::endl;
		}
		else
		{
			Zombie* zombieClose = scene->CheckZombieClose(this);
			if(zombieClose != nullptr)
			{
				Bullet* bullet = AddBullet(scene, zombieClose);
			}
			
		}
	}
	else
	{
		AddBullet(scene, nullptr);
	}
}

bool Plant::TransitionTo(State newState)
{
	if (mTransitions[(int)mState][(int)newState])
	{
		mActions[(int)newState]->Start(this);
		mState = newState;

		return true;
	}

	return false;
}

void Plant::UpdateAction(float dt)
{
	mActions[(int)mState]->Update(this, dt);
}

bool Plant::Shoot()
{
	if (TransitionTo(State::Shooting) == false || mAmmo <= 0)
		return false;
	
	mAmmo--;

	return true;
}

bool Plant::Reload()
{
	if (TransitionTo(State::Reloading) == false)
		return false;

	return true;
}

Bullet* Plant::AddBullet(Scene* pScene, Entity* zombieClose)
{
	if(Shoot())
	{
		Bullet* bullet = pScene->CreateEntity<Bullet>(10, sf::Color::White);
		bullet->Start(this, zombieClose);
		return bullet;
	}
	return nullptr;
}

void Plant::OnCollision(Entity* other)
{
	if (other->IsTag((int)PVZScene::Tag::Zombie))
	{
		this->Destroy();
		std::cout << "Dead Plant !" << std::endl;
	}
}

sf::Vector2i Plant::GetCharger()
{
	return sf::Vector2i(mAmmo, mCapacity);
}