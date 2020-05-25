#pragma once



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"
#include <Box2D/Box2D.h>

namespace Engine
{


	class PlayerShape : public Object
	{
	private:
		glm::mat4 FCmodel;
		b2Vec2 m_position;
	public:
		PlayerShape() {}; //!< Default Constructor
		PlayerShape(b2World* world, const glm::vec2& position, const glm::vec2& size, const float& orientation, const glm::vec3& colour); //!< Complete Contructor
		void draw(glm::mat4 projection, glm::mat4 view); //!< draws the shape
		void update(); //!< updates the position of the shape
		void movement(b2Vec2 movement); //!< moves the player
		void playerStopped();
		b2Vec2 playerPosition();
		
		

		
	};
}