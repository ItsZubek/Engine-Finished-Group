
#include "engine_pch.h"
#include "platform\OpenGL\Rendering\OpenGLSetBackFaceCullingCommand.h"
#include <glad/glad.h>

namespace Engine
{
	void OpenGLSetBackFaceCullingCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}
}