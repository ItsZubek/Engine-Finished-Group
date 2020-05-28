#include "engine_pch.h"
#include "platform/OpenGL/Rendering/OpenGLSetDepthTestLessCommand.h"
#include <glad/glad.h>

namespace Engine
{
	void OpenGLSetDepthTestLessCommand::action()
	{
		if (m_enabled)
		{
			// Enable standard depth detest (Z-buffer)
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}
}