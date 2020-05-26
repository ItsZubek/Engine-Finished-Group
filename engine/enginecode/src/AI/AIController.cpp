#include "AI/AIController.h"
#include "engine_pch.h"

namespace Engine
{
	AIController::AIController()
	{

	}


	AIController::~AIController()
	{

	}

	void AIController::reset()
	{
		action = 1;
	}



	void AIController::move()
	{

		if (action == 1) //Idle
		{
			right = false;
			forward = true;

		}
		else if (action == 2) //Attack
		{

			forward = false;
		}
		else if (action == 3)
		{

			right = true;
			forward = false;
		}
		else if (action == 4)
		{
			right = false;
			forward = true;

		}
		else if (action == 5) //destroy self
		{
			
		}
		else if (action == 6)
		{

			forward = true;  backward = false;
			right = true;
		}

	}


	void AIController::collided()
	{
		if (collision == true) { action = 5; }
		
	}

	void AIController::Locate()
	{
	}


	void AIController::ShipShoot()
	{
		if (enemyMarked == true)
		{
			if (lineOfSight == true)
			{
				firing = true;
			}
			if (lineOfSight == false)
			{
				firing = false;
				enemyMarked = false;
				
			}
		}
	}




	bool AIController::isFiring()
	{
		return firing;
	}
}


