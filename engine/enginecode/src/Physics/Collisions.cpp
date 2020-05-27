
#include "engine_pch.h"
#include "Physics/Collisions.h"


#include "systems/MyLogger.h"

namespace Engine
{
	void Collisions::beginCollisions(b2Contact* collisions)
	{
		// creates contact listener for a body
		b2Body* bodyA = collisions->GetFixtureA()->GetBody(); // creates contact listener for a body
		b2Body* bodyB = collisions->GetFixtureB()->GetBody();

		// if nothing points to it return nothing=
		if (bodyA->GetUserData() == nullptr) return;
		if (bodyB->GetUserData() == nullptr) return;

		// gets the user data of the contact listeners
		std::pair<std::string, void*> dataA = *(std::pair<std::string, void*>*)bodyA->GetUserData();
		std::pair<std::string, void*> dataB = *(std::pair<std::string, void*>*)bodyB->GetUserData();

		if (dataA.first == typeid(BulletShape).name())
		{
			if (dataB.first == typeid(EnemyShape).name())
			{
				//if contact between a dynamic circle and a sensor
				EnemyShape* enemies = static_cast<EnemyShape*>(dataA.second);
				if (enemies != nullptr)
				{
					//enemies->Destroy()
					ENGINE_CORE_CRITICAL("Collision Occured");
				}
			}
		}
		else if (dataB.first == typeid(BulletShape).name())
		{
			if (dataA.first == typeid(EnemyShape).name())
			{
				//if contact between a dynamic circle and a sensor
				EnemyShape* enemies = static_cast<EnemyShape*>(dataA.second);
				if (enemies != nullptr)
				{
					ENGINE_CORE_CRITICAL("Collision Occured");
					
				}
			}
		}

	}

	void Collisions::endCollisions(b2Contact* collisions)
	{
		b2Body* bodyA = collisions->GetFixtureA()->GetBody();
		b2Body* bodyB = collisions->GetFixtureB()->GetBody();

		if (bodyA->GetUserData() == nullptr) return;
		if (bodyB->GetUserData() == nullptr) return;

		std::pair<std::string, void*> dataA = *(std::pair<std::string, void*>*)bodyA->GetUserData();
		std::pair<std::string, void*> dataB = *(std::pair<std::string, void*>*)bodyB->GetUserData();

		if (dataA.first == typeid(BulletShape).name())
		{
			if (dataB.first == typeid(EnemyShape).name())
			{
				// if end of contact between circle and sensor 
				EnemyShape* enemies = static_cast<EnemyShape*>(dataA.second);
				if (enemies != nullptr)
				{
					ENGINE_CORE_CRITICAL("Collision Ended");
				}
			}
			else if (dataA.first == typeid(BulletShape).name())
			{
				if (dataB.first == typeid(EnemyShape).name())
				{
					EnemyShape* enemies = static_cast<EnemyShape*>(dataA.second);
					if (enemies != nullptr)
					{
						ENGINE_CORE_CRITICAL("Collision Ended");
					}
					
				}
			}

		}
	}
}