#pragma once

#include "Object.h"
#include "PlayerShape.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

	class BulletShape : public Object
	{
	private:
		glm::mat4 m_bulletModel;
		bool m_bulletFired = false;
		int m_bulletCounter = 0;

	public:
		BulletShape() {}; //!< Default Constructor
		BulletShape(b2World* world, const glm::vec2& position, const glm::vec2& size, const float& orientation, const glm::vec3& colour); //!< Complete Constructor
		void update(); //!< updates the position of the bullet
		void draw(glm::mat4 projection, glm::mat4 view); //!< Draws the bullet shape
		void fire(b2Vec2 movement); //!< moves the bullet Shape
		void Fired();
		void setPosition(b2Vec2 position);
		
	};
}