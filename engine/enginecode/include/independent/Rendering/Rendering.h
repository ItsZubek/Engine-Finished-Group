 #pragma once

namespace Engine
{

	class Rendering
	{
	public:
		virtual void actionCommand(RenderCommand* command) = 0; //!< Action for rendering
		virtual void beginScene(const SceneData& sceneData) = 0;
		virtual void endScene() = 0; //!< End of scene
		virtual void submit(const std::shared_ptr<Material>& material) = 0;
		virtual void flush() = 0; //!< Draw Everything

		static Rendering* createBasic3D();
	};
}
