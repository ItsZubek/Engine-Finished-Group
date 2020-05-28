#include "engine_pch.h"
#include "include/independent/platform/OpenGL/OpenGLRendering.h"
#include <glad/glad.h>

namespace Engine
{
	void OpenGLRendering::actionCommand(RenderCommand * command)
	{
		command->action();
		delete command;
	}

	void OpenGLRendering::submit(const std::shared_ptr<Material>& material)
	{
		auto shader = material->getShader();
		shader->bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->bind();

		auto perDrawData = material->getData();
		for (auto dataPair : perDrawData)
		{
			shader->uploadData(dataPair.first, dataPair.second);
		}
		glDrawElements(GL_QUADS, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}
}