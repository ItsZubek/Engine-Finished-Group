#pragma once
#include "windows/Renderer.h"
#include <memory>

#include <glad/glad.h>

namespace Engine {

	class OpenGLRendering : public Renderer
	{
	private:
	public:
		void actionCommand(RenderCommand* command) override;
		void beginScene(const SceneData& sceneData) override {};
		void endScene() override {};
		void submit(const std::shared_ptr<Material>& material) override;
		void flush()override {};
	};
}