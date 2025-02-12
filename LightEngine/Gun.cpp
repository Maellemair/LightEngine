#include "Gun.h"
#include "Actions.h"

Plant::Plant(int capacity, float reloadTime, float shootTime)
{
    mAmmo = capacity;
    mCapacity = capacity;

	mActions[(int)State::Full] = new ActionFull();
    mActions[(int)State::Loaded] = new ActionLoaded();
	mActions[(int)State::Shooting] = new ActionShoot(shootTime);
	mActions[(int)State::Empty] = new ActionEmpty();
	mActions[(int)State::Reloading] = new ActionReload(reloadTime);

	TransitionTo(State::Full);
}

void Plant::Update(float deltaTime)
{
	mActions[(int)mState]->Update(this, deltaTime);
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

    return true;
}
