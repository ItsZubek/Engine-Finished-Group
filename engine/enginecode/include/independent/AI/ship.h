
#include "Profiler/profiler.h"
#include "Physics/Object.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	class Ship : public Object
	{
	private:
		glm::mat4 EnemyShip;
		int action;
		int counter = 0;
		int rando;
		
	public:
		
		Ship() {};
		Ship(b2World* world, const glm::vec2& position, const glm::vec2& size, const float& orientation, const glm::vec3& colour); //!< Complete Contructor
		void draw(glm::mat4 projection, glm::mat4 view); //!< draws the shape
		void update(b2World* world); //!< updates the position of the shape

			// Movement methods
		void goForward(); //!< Set the ship to go forwards
		void goBackward(); //!< Set the ship to go backwards
		void goLeft(); //!< Set the ship to go left
		void goRight(); //!< Set the ship to go right
		void stop(); //!< Stop the ship movement
		void Destroy(b2World* world);

		void Move();
		
		
		void movement(b2Vec2 movement);
		void raycast(b2World* world);
	};


	class MyRayCastCallback : public b2RayCastCallback
	{
	public:
		MyRayCastCallback()
		{
			m_fixture = NULL;
		}

		float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
			const b2Vec2& normal, float fraction)
		{
			m_fixture = fixture;
			m_point = point;
			m_normal = normal;
			m_fraction = fraction;
			return fraction;
		}

		b2Fixture* m_fixture;
		b2Vec2 m_point;
		b2Vec2 m_normal;
		float m_fraction;
	
	};
	

}
