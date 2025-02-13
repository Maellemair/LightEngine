#pragma once

#include <iostream>
#include "Plant.h"

inline void Print(const std::string& message)
{
	//system("cls");
	//std::cout << message << std::endl;
}

class Action
{
public:
	virtual void Start(Plant* pPlant) = 0;
	virtual void Update(Plant* pPlant, float dt) = 0;
};

class ActionIdle : public Action
{
public:
	void Start(Plant* pPlant) override
	{
		Print("No zombies in sight !");
	}

	void Update(Plant* pPlant, float dt) override
	{
	}
};

class ActionFull : public Action
{
public:
	void Start(Plant* pPlant) override
	{
		Print("Ready to shoot, Ammo: " + std::to_string(pPlant->mAmmo));
	}

	void Update(Plant* pPlant, float dt) override
	{
		pPlant->TransitionTo(Plant::State::Idle);
	}
};

class ActionLoaded : public Action
{
public:
	void Start(Plant* pPlant) override
	{
		Print("Ready to shoot, Ammo: " + std::to_string(pPlant->mAmmo));
	}

	void Update(Plant* pPlant, float dt) override
	{
		//pPlant->TransitionTo(Plant::State::Idle);
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

	void Start(Plant* pPlant) override
	{
		Print("Bang!");
	}

	void Update(Plant* pPlant, float dt) override
	{
		mShootProgress += dt;

		if (mShootProgress < mShootTime)
			return;

		mShootProgress = 0.0f;
		if (pPlant->mAmmo > 0)
		{
			pPlant->TransitionTo(Plant::State::Loaded);
		}
		else
		{
			pPlant->TransitionTo(Plant::State::Empty);
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

	void Start(Plant* pPlant) override
	{
		Print("Reloading...");
	}

	void Update(Plant* pPlant, float dt) override
	{
		mReloadProgress += dt;
		if (mReloadProgress < mReloadTime)
			return;

		pPlant->mAmmo = pPlant->mCapacity;
		mReloadProgress = 0.0f;

		pPlant->TransitionTo(Plant::State::Full);
	}
};

class ActionEmpty : public Action
{
public:
	void Start(Plant* pPlant) override
	{
		Print("Empty!");
	}

	void Update(Plant* pPlant, float dt) override
	{
		pPlant->TransitionTo(Plant::State::Reloading);
	}
};
