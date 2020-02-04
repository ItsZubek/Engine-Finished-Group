/** \file OpenGLBuffer.cpp
*/
#include "engine_pch.h"
#include "platform/OpenGL/OpenGLBuffer.h"
#include <glad/glad.h>

namespace Engine {

	//VERTEX BUFFER

	OpenGLVertexBuffer::OpenGLVertexBuffer(float * vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}


	//INDEX BUFFER

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	//Vertex Array

	OpenGLVertexArray::OpenGLVertexArray()
	{

	}
	void OpenGLVertexArray::bind()
	{

	}
	void OpenGLVertexArray::unbind()
	{

	}
	void OpenGLVertexArray::setVertexBuffer()
	{

	}
	void OpenGLVertexArray::setIndexBuffer()
	{

	}
	std::shared_ptr<VertexBuffer> OpenGLVertexArray::getVertexBuffer()
	{

	}
	std::shared_ptr<IndexBuffer>  OpenGLVertexArray::getIndexBuffer()
	{

	}
	unsigned int OpenGLVertexArray::getDrawCount()
	{

	}
}