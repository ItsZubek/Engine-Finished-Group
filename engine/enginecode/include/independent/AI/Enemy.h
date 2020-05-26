
#include "ship.h"
namespace Engine
{
	class Enemy : Ship
	{
	protected:
		
		

	public:
		Enemy();
		//FSM Public methods, set states and variables
		virtual void reset() = 0; //Reset Variables
		virtual void Spawn() = 0; //spawn in random position
		virtual void move()  = 0; //Move the Ship
		virtual void onCollision(); //destroys enemy on collision
		virtual bool isFiring() = 0;
		
		// Box2D Position of the enemy in x
		 // Box2D Position of the enemy in y
		bool canAttack;
		bool canSee;
	};


	




}