#pragma once

#include "Entity.h"

class Bullet;
class Action;
class Zombie;

class Plant : public Entity
{
public:

	enum State
	{
		Idle,
		Shooting,
		Full,
		Loaded,
		Empty,
		Reloading,

		Count
	};
	static constexpr int STATE_COUNT = static_cast<int>(State::Count);

private:
	int mAmmo;
	int mCapacity;

	State mState = State::Idle;

	int mTransitions[STATE_COUNT][STATE_COUNT] =
	{
		// Idle, Shooting, Full, Loaded, Empty, Reloading
		{   0,       1,      1,     0,     0,       0 }, // Idle
		{   1,       0,      0,     1,     1,       0 }, // Shooting
		{   1,       1,      0,     0,     0,       0 }, // Full
		{   1,       1,      0,     0,     0,       1 }, // Loaded
		{   0,       0,      0,     0,     0,       1 }, // Empty
		{   1,       0,      1,     0,     0,       0 }  // Reloading
	};

	Action* mActions[STATE_COUNT];

public:
	
	void Start(float posY, int capacity, float shootTime, float reloadTime);
	void OnUpdate();
	bool TransitionTo(State newState);
	void UpdateAction(float dt);
	bool Shoot();
	bool Reload();
	Bullet* AddBullet(Scene* pScene, Entity* zombieClose);
	void OnCollision(Entity* other) override;

	sf::Vector2i GetCharger();

	friend class ActionIdle;
	friend class ActionFull;
	friend class ActionLoaded;
	friend class ActionShoot;
	friend class ActionEmpty;
	friend class ActionReload;
};
	


