#pragma once



namespace Engine
{
	class RenderCommand
	{
	public:
		virtual void action() = 0;

		static RenderCommand* ClearDepthColourBufferCommand();
		static RenderCommand* SetClearColourCommand(float r, float g, float b, float a);
		static RenderCommand* SetDepthTestLessCommand(bool enabled);
		static RenderCommand* SetBackFaceCullingCommand(bool enabled);
	};
}