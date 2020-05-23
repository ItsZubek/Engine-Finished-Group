#pragma once

#include "Object.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	class EnemyShape : public Object
	{
	private:
		glm::mat4 EnemyModel;
	public:
		EnemyShape() {}; //!< Default Constructor
		EnemyShape(b2World* world, const glm::vec2& position, const glm::vec2& size, const float& orientation, const glm::vec3& colour); //!< Complete Constructor)
		void draw(glm::mat4 projection, glm::mat4 view); //!< draws the shape
		void Destroy(); //!< destroys the enemy
	};
}