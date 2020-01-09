/** \file WindowsWindow.h
*/
#pragma once
#include "windows/window.h"
#include "../glfw/include/GLFW/glfw3.h"
#include "windows/graphicsContext.h"

namespace Engine {
	/**
\class WindowsWindow
Used to generate a glfw window, implements components of a Window class
*/
	class WindowsWindow : public Window
	{
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		virtual void init(const WindowProperties & properties);
		virtual void Shutdown();
		WindowProperties m_properties;
		float m_aspectRatio;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();
		void onUpdate() override;
		void onResize(unsigned int width, unsigned int height) override;
		void setVSync(bool VSync) override;
		inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
		inline unsigned int getWidth() const override { return m_Data.Width; }
		inline unsigned int getHeight() const override { return m_Data.Height; }
		inline virtual void* getNativeWindow() const override { return m_Window; }
		inline bool isFullScreenMode() const override { return m_properties.m_isFullScreen; }
		bool isVSync() const override;

		
	};
}