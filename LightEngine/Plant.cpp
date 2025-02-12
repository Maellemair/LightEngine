#include "Plant.h"
#include "Bullet.h"
#include "PVZScene.h"

void Plant::Start(float posY, int capacity, float shootTime, float reloadTime)
{
	SetPosition(70, posY);
	SetRigidBody(true); 
	SetTag((int)PVZScene::Tag::Plant);

	mAmmo = capacity;
	mCapacity = capacity;

	mActions[(int)State::Full] = new ActionFull();
	mActions[(int)State::Loaded] = new ActionLoaded();
	mActions[(int)State::Shooting] = new ActionShoot(shootTime);
	mActions[(int)State::Empty] = new ActionEmpty();
	mActions[(int)State::Reloading] = new ActionReload(reloadTime);

	TransitionTo(State::Full);
}

void Plant::OnUpdate()
{
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

void Plant::AddBullet(Scene* pScene)
{
	if()
	{
		Bullet* bullet = pScene->CreateEntity<Bullet>(10, sf::Color::White);
		bullet->Start(this);
	}
}
