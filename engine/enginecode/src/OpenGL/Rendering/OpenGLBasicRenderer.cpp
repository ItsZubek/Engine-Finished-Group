
#include "engine_pch.h"
#include "platform\OpenGL\Rendering\OpenGLBasicRenderer.h"

namespace Engine
{
	void OpenGLBasicRenderer::actionCommand(RenderCommand* command)
	{
		command->action();
		delete command;
	}
	/*void OpenGLBasicRenderer::beginScene(const SceneData& sceneData)
	{
	}*/
	void OpenGLBasicRenderer::endScene()
	{

	}
	/*void OpenGLBasicRenderer::submit(const std::shared_ptr<Material>& material)
	{
		auto shader = material->getShader();
		shader->Bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->bind();

		auto uniformData = material->getData();
		for (auto dataPair : uniformData)
		{
			shader->
		}

		glDrawElements(GL_QUADS, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}*/
	
}