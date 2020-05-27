#include "engine_pch.h"
#include "platform/OpenGL/Rendering/OpenGLSetClearColourCommand.h"
#include <glad/glad.h>

namespace Engine
{
	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_Red, m_Green, m_Blue, m_Alpha);
	}
}