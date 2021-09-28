#pragma once

#include "OrangeEngineCore/Graphics/OpenGL/VertexBuffer.h"

namespace OrangeEngine
{
	class VertexArray
	{
	public:
		
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&& vertex_array) noexcept;
		VertexArray(VertexArray&& vertex_array) noexcept;

		void add_buffer(const VertexBuffer& vertex_buffer);
		void bind() const;
		static void unbind();

	private:
		unsigned int m_id = 0;
		unsigned int m_items_quantity = 0;
	};
}