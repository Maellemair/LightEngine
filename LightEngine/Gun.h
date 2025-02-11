#pragma once

#include <string>

class Action;

class Gun
{
public:
    enum class State
    {
        Full,
        Loaded,
        Empty,
        Shooting,
        Reloading,

        Count
    };

    static constexpr int STATE_COUNT = static_cast<int>(State::Count);

private:
    int mAmmo;
    int mCapacity;

    State mState = State::Full;

    int mTransitions[STATE_COUNT][STATE_COUNT] =
    {
        // Full, Loaded, Empty, Shooting, Reloading
        {  1,     0,      0,     1,        0 }, // Full
        {  0,     0,      0,     1,        1 }, // Loaded
        {  0,     0,      0,     0,        1 }, // Empty
        {  0,     1,      1,     0,        0 }, // Shooting
        {  1,     0,      0,     0,        0 }  // Reloading
    };

	Action* mActions[STATE_COUNT];

public:
    Gun(int capacity, float reloadTime = 2.0f, float shootTime = 0.5f);

    void Update(float deltaTime);

    bool TransitionTo(State newState);

    bool Shoot();

    bool Reload();

    friend class ActionFull;
	friend class ActionLoaded;
	friend class ActionShoot;
	friend class ActionEmpty;
	friend class ActionReload;
};
