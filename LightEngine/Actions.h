#pragma once

#include "Plant.h"
#include <iostream>

inline void Print(const std::string& message)
{
	system("cls");
	std::cout << message << std::endl;
}

class Plant;

class Action
{
public:
	virtual void Start(Plant* pGun) = 0;
	virtual void Update(Plant* pGun, float dt) = 0;
};

class ActionIdle : public Action
{
public:
	void Start(Plant* pGun) override
	{
		Print("No zombies in sight !");
	}

	void Update(Plant* pGun, float dt) override
	{
	}
};

class ActionFull : public Action
{
public:
	void Start(Plant* pGun) override
	{
		Print("Ready to shoot, Ammo: " + std::to_string(pGun->mAmmo));
	}

	void Update(Plant* pGun, float dt) override
	{
	}
};

class ActionLoaded : public Action
{
public:
	void Start(Plant* pGun) override
	{
		Print("Ready to shoot, Ammo: " + std::to_string(pGun->mAmmo));
	}

	void Update(Plant* pGun, float dt) override
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

	void Start(Plant* pGun) override
	{
		Print("Bang!");
	}

	void Update(Plant* pGun, float dt) override
	{
		mShootProgress += dt;
		if (mShootProgress < mShootTime)
			return;

		mShootProgress = 0.0f;
		if (pGun->mAmmo > 0)
		{
			pGun->TransitionTo(Plant::State::Loaded);
		}
		else
		{
			pGun->TransitionTo(Plant::State::Empty);
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

	void Start(Plant* pGun) override
	{
		Print("Reloading...");
	}

	void Update(Plant* pGun, float dt) override
	{
		mReloadProgress += dt;
		if (mReloadProgress < mReloadTime)
			return;

		pGun->mAmmo = pGun->mCapacity;
		mReloadProgress = 0.0f;

		pGun->TransitionTo(Plant::State::Full);
	}
};

class ActionEmpty : public Action
{
public:
	void Start(Plant* pGun) override
	{
		Print("Empty!");
	}

	void Update(Plant* pGun, float dt) override
	{
	}
};
