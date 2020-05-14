#pragma once

#include "Object.h"

namespace Engine
{
	class PlayerShape : Object
	{
	
	public:
		PlayerShape() {} //!< default Constructor
		PlayerShape(b2World* world, const b2Vec2& position, const b2Vec2& size, float& orientation); //!< Complete Constructor 
		void drawShape(b2Vec2* vertices, b2Vec2 centre, float angle); //!< draws a shape
		void update(); //!< Update rendering infomation 
		void Movement(b2Vec2 movement); //!< moves the player by a given force
	};
}
