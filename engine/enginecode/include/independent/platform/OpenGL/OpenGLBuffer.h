/** \file OpenGLVertexBuffer.h
*/
#pragma once

#include "windows/Buffer.h"

namespace Engine {
	/**
\class OpenGLVertexBuffer
Vertex Buffer for OpenGL
*/
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind()const;
		virtual void UnBind()const;
	private:
		uint32_t m_RendererID;

	};
	/**
\class OpenGLIndexBuffer
Index Buffer for OpenGL
*/
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind()const;
		virtual void UnBind()const;
		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	};

	/**
\class OpenGLVertexArray
Vertex Array for OpenGL
*/
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		void bind();
		void unbind();
		void setVertexBuffer();
		void setIndexBuffer();
		std::shared_ptr<VertexBuffer> getVertexBuffer();
		std::shared_ptr<IndexBuffer> getIndexBuffer();
		unsigned int getDrawCount();
	};
}