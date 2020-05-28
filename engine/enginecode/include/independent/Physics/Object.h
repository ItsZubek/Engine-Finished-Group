#pragma once

#include <Box2D/Box2D.h>

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

namespace Engine
{

	class Object
	{
	protected:
		b2Body* m_body = nullptr; //!< Box2D body, used by objects to update things like position
		float m_Density = 1.0f; //!< used to give mass
		float m_Friction = 0.4f; //!< friction used to slow objects down 
		float m_Restitution = 0.6f; //!< bouncyness of stuff
	public:
		void setUserData(void* data) { m_body->SetUserData(data); }; //!< \fn Set the user data of the body
	};
}
