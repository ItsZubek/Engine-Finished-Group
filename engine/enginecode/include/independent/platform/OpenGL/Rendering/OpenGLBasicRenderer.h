#pragma once
#include "Rendering/Rendering.h"
#include "Rendering/RenderCommand.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{
	class OpenGLBasicRenderer : Rendering
	{
	public:
		void actionCommand(RenderCommand* command) override; //!< Action for rendering
		void beginScene(const SceneData& sceneData) override;
		void endScene() override; //!< End of scene
		void submit(const std::shared_ptr<Material>& material) override;
		void flush() override; //!< Draw Everything

		
	};
}