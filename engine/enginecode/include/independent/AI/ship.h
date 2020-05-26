

#include "Physics/Object.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Engine
{
	class Ship : public Object
	{
	private:
		glm::mat4 EnemyShip;
		b2Vec2 m_position;
	protected:
		
		
		
		
		

		
		
	public:
		void movement(b2Vec2 movement, float spin);
		Ship() {};
		Ship(b2World* world, const glm::vec2& position, const glm::vec2& size, const float& orientation, const glm::vec3& colour); //!< Complete Contructor
		void draw(glm::mat4 projection, glm::mat4 view); //!< draws the shape
		void update(); //!< updates the position of the shape
		void raycast(b2World* m_world, b2Vec2 p1, b2Vec2 p2);
			// Movement methods
		void goForward(); //!< Set the ship to go forwards
		void goBackward(); //!< Set the ship to go backwards
		void goLeft(); //!< Set the ship to go left
		void goRight(); //!< Set the ship to go right
		void ShipRotateLeft(); //!< Set the ship to go left
		void ShipRotateRight(); //!< Set the ship to go right
		void stop(); //!< Stop the ship movement
		//!< Box2D Record the prevoius position
		 //!< Box2D Go back to the prevoius position
		void Destroy();
		bool canSee;
		b2Vec2 EnemyPosition();
		
	};


	

}