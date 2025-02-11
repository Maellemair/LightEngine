#pragma once

#include "Gun.h"
#include <iostream>

inline void Print(const std::string& message)
{
	system("cls");
	std::cout << message << std::endl;
}

class Action
{
public:
	virtual void Start(Gun* pGun) = 0;
	virtual void Update(Gun* pGun, float dt) = 0;
};

class ActionFull : public Action
{
public:
	void Start(Gun* pGun) override
	{
		Print("Ready to shoot, Ammo: " + std::to_string(pGun->mAmmo));
	}

	void Update(Gun* pGun, float dt) override
	{
	}
};

class ActionLoaded : public Action
{
public:
	void Start(Gun* pGun) override
	{
		Print("Ready to shoot, Ammo: " + std::to_string(pGun->mAmmo));
	}

	void Update(Gun* pGun, float dt) override
	{
	}
};

class ActionShoot : public Action
{
	float mShootTime;
	float mShootProgress = 0.f;

public:
	ActionShoot(float shootTime)
	{
		mShootTime = shootTime;
	}

	void Start(Gun* pGun) override
	{
		Print("Bang!");
	}

	void Update(Gun* pGun, float dt) override
	{
		mShootProgress += dt;
		if (mShootProgress < mShootTime)
			return;

		mShootProgress = 0.0f;
		if (pGun->mAmmo > 0)
		{
			pGun->TransitionTo(Gun::State::Loaded);
		}
		else
		{
			pGun->TransitionTo(Gun::State::Empty);
		}
	}
};

class ActionReload : public Action
{
	float mReloadTime;
	float mReloadProgress = 0.f;

public:
	ActionReload(float reloadTime)
	{
		mReloadTime = reloadTime;
	}

	void Start(Gun* pGun) override
	{
		Print("Reloading...");
	}

	void Update(Gun* pGun, float dt) override
	{
		mReloadProgress += dt;
		if (mReloadProgress < mReloadTime)
			return;

		pGun->mAmmo = pGun->mCapacity;
		mReloadProgress = 0.0f;

		pGun->TransitionTo(Gun::State::Full);
	}
};

class ActionEmpty : public Action
{
public:
	void Start(Gun* pGun) override
	{
		Print("Empty!");
	}

	void Update(Gun* pGun, float dt) override
	{
	}
};
