#pragma once

#include "Object.h"

namespace Engine
{
	class PlayerShape : Object
	{
	private:
		const float m_Pixel2Meters = 20;
		const float m_Meters2Pixel = 1 / m_Pixel2Meters;
	public:
		PlayerShape() {} //!< default Constructor
		PlayerShape(b2World* world, const b2Vec2& position, const b2Vec2& size, float& orientation); //!< Complete Constructor 
		void drawShape(b2Vec2* vertices, b2Vec2 centre, float angle); //!< draws a shape
	};
}
