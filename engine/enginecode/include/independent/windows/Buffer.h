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
		virtual void Bind() const= 0;
		virtual void UnBind() const= 0;

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
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setVertexBuffer() const = 0;
		virtual void setIndexBuffer() const = 0;
		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;
		virtual unsigned int getDrawCount() const = 0;

		static VertexArray * create();
	};
}
