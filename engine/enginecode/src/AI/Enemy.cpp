#include "..\..\include\independent\AI\Enemy.h"
namespace Engine
{
	Enemy::Enemy()
	{
	}

	const float Enemy::moveConst = 4.0f; // Total amount of movement allowed each timestep
	const float Enemy::rotMoveConst = 2.0f; // Total amount of rotational movement allowed each timestep for the tank
	const float Enemy::turRotMoveConst = 2.0f; // Total amount of rotational movement allowed each timestep for the turrent


	void Enemy::Spawn()
	{
		//spawn random location
	}

	

	void Enemy::move()
	{
		if (canSee)
		{

		}

	}

	
	void Enemy::onCollision()
	{
	//delete enemy
	}




}