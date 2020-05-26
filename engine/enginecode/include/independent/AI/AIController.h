#ifndef TANK_CONTROLLER_H
#define TANK_CONTROLLER_H

#include "Enemy.h"
#include "Physics/PlayerShape.h"
#include <iostream>

namespace Engine
{

	class AIController : public Enemy
	{

	public:
		AIController();
		~AIController();
		//Box2D Draw
		void move();
		void reset();
		void collided();
		bool collision;
		void Locate();
		void ShipShoot();
		bool isFiring();
		int action;
	private:
		float getEnemyDistance;
		int Angle = 0;
		bool enemyMarked = false;
		bool firing = false;
		bool lineOfSight = false;
	

	protected:
	};
#endif
}