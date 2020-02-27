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
		glCreateVertexArrays(1, &m_Renderer);
	}
	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_Renderer);
	}
	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) const
	{
		glBindVertexArray(m_Renderer);

		vertexBuffer->Bind();

		unsigned int index = 0;
		const auto layout = vertexBuffer->getBufferLayout();
		for (const auto&  elements : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, ShaderDataTypeComponentCount(elements.m_datatype),
				ShaderDataTypeToOpenGLType(elements.m_datatype)
				, elements.m_normalised,
				layout.getStride(),
				(const void*)elements.m_offset);
			index++;
		}

	}
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer)
	{
		glBindVertexArray(m_Renderer);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	std::shared_ptr<VertexBuffer> OpenGLVertexArray::getVertexBuffer() const
	{
		return m_VertexBuffer;
	}
	std::shared_ptr<IndexBuffer>  OpenGLVertexArray::getIndexBuffer() const
	{
		return m_IndexBuffer;
	}
	unsigned int OpenGLVertexArray::getDrawCount() const
	{
		return m_IndexBuffer->GetCount();
	}
}