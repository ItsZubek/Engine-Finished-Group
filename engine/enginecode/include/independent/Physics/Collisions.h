#pragma once

#include <Box2D/Box2D.h>

namespace Engine
{
	class Collisions : public b2ContactListener
	{
	public:
		void beginCollisions(b2Contact* collisions); //!< starts at the start of the collision
		void endCollisions(b2Contact* collisions); //!< concludes the contact between two objects
	};
}