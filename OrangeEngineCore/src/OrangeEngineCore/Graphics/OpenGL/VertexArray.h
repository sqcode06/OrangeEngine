#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace OrangeEngine
{
	class VertexArray
	{
	public:
		
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&& vertexArray) noexcept;
		VertexArray(VertexArray&& vertexArray) noexcept;

		void add_vbo(const VertexBuffer& vertexBuffer);
		void set_ibo(const IndexBuffer& indexBuffer);
		void bind() const;
		static void unbind();
		size_t get_indices_quantity() const { return m_indices_quantity; }

	private:
		unsigned int m_id = 0;
		unsigned int m_items_quantity = 0;
		size_t m_indices_quantity = 0;
	};
}