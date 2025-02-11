#include "Gun.h"
#include "Actions.h"

Gun::Gun(int capacity, float reloadTime, float shootTime)
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

void Gun::Update(float deltaTime)
{
	mActions[(int)mState]->Update(this, deltaTime);
}

bool Gun::TransitionTo(State newState)
{
    if (mTransitions[(int)mState][(int)newState])
    {
		mActions[(int)newState]->Start(this);
        mState = newState;

        return true;
    }

    return false;
}

bool Gun::Shoot()
{
    if (TransitionTo(State::Shooting) == false)
        return false;

    mAmmo--;

    return true;
}

bool Gun::Reload()
{
    if (TransitionTo(State::Reloading) == false)
        return false;

    return true;
}
