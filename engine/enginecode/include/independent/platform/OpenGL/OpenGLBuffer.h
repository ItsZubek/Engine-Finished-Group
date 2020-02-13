/** \file OpenGLVertexBuffer.h
*/
#pragma once

#include "windows/Buffer.h"

namespace Engine 
{
	/**
\class OpenGLVertexBuffer
Vertex Buffer for OpenGL
*/
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;
		virtual void Bind()const override;
		virtual void UnBind()const override;

		virtual void setBufferLayout(const BufferLayout& layout) override { m_BufferLayout = layout; }
		virtual const BufferLayout& getBufferLayout() const override { return m_BufferLayout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_BufferLayout;

	};
	/**
\class OpenGLIndexBuffer
Index Buffer for OpenGL
*/
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer() override;
		virtual void Bind()const override;
		virtual void UnBind()const override;
		virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	};

	/**
\class OpenGLVertexArray
Vertex Array for OpenGL
*/
#include "windows/ShaderDataType.h"

	class OpenGLVertexArray : public VertexArray
	{
	private:
		uint32_t m_Renderer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		BufferLayout m_BufferLayout;
		BufferElement m_BufferElement;
	public:
		OpenGLVertexArray();
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void setVertexBuffer() const override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) override;
		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const override;
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const override;
		virtual unsigned int getDrawCount() const override;
	};
}