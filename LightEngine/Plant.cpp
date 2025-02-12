#include "Plant.h"
#include "Bullet.h"
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

void Plant::Update(Entity* pZombie)
{
	if(pZombie != nullptr)
	{
		float x = pZombie->GetPosition().x - GetPosition().x;

		if (x <= 400)
		{
			AddBullet(GetScene());
		}
		else
		{
			Reload();
		}
	}
	if(mAmmo <= 2)
	{
		Reload();
	}
	mActions[(int)mState]->Update(this, GetDeltaTime());
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

bool Plant::Shoot()
{
	if (TransitionTo(State::Shooting) == false)
		return false;

	mAmmo--;

	return true;
}

bool Plant::Reload()
{
	if (TransitionTo(State::Reloading) == false)
		return false;
}

void Plant::AddBullet(Scene* pScene)
{
	if(Shoot())
	{
		Bullet* bullet = pScene->CreateEntity<Bullet>(10, sf::Color::White);
		bullet->Start(this);
	}
}

sf::Vector2i Plant::GetCharger()
{
	return sf::Vector2i(mAmmo, mCapacity);
}