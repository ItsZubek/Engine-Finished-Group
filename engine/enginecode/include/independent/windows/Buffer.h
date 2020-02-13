/** \file Buffer.h
*/

#pragma once


namespace Engine {
	/**
\class Interface class for Vertex buffers
*/
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void setBufferLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& getBufferLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};
	/**
\class Interface class for Index buffers
*/
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

	/**
\class Interface class for vertex array
*/
	class VertexArray
	{
	private:
		
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setVertexBuffer() const = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) = 0;
		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;
		virtual unsigned int getDrawCount() const = 0;

		static VertexArray* create();
	};

	/**
	\class for Buffer Element
	*/

#include "ShaderDataType.h"

	class BufferElement
	{
	public:
		ShaderDataType m_datatype;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalised;

		BufferElement() {};
		BufferElement(ShaderDataType dataType, bool normalised = false) : m_datatype(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalised(normalised) {};
	};

	/**
	\class for Buffer Layout
	*/
#include <vector>
#include <initializer_list>
#include <iterator>
	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_elements;
		unsigned int m_stride;

		void calcStrideandOffset()
		{
			unsigned int offset = 0;
			m_stride = 0;
			for (auto& elements : m_elements)
			{
				elements.m_offset = offset;
				offset += elements.m_size;
				m_stride += elements.m_size;
			}
		}
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements)
		{
			calcStrideandOffset();
		}

		inline unsigned int getStride() const { return m_stride; }
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	};
}


