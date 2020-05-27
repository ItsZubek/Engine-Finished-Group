#include "engine_pch.h"
#include "platform/OpenGL/Rendering/OpenGLClearDepthColourBufferCommand.h"
#include <glad/glad.h>

namespace Engine
{
	void OpenGLClearDepthColourBufferCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}