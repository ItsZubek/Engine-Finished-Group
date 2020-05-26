#pragma once

#include "Rendering/RenderCommand.h"

namespace Engine
{
	class OpenGLSetClearColourCommand : public RenderCommand
	{
	private:
		float m_Red, m_Green, m_Blue, m_Alpha;
	public:
		OpenGLSetClearColourCommand(float red, float green, float blue, float alpha) : m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(alpha) {};
		void action() override;
	};
}