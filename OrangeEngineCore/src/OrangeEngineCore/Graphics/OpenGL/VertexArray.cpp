#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	VertexArray& VertexArray::operator=(VertexArray&& vertex_array) noexcept
	{
		m_id = vertex_array.m_id;
		m_items_quantity = vertex_array.m_id;
		vertex_array.m_id = 0;
		vertex_array.m_items_quantity = 0;
		return *this;
	}

	VertexArray::VertexArray(VertexArray&& vertex_array) noexcept
		:m_id(vertex_array.m_id),
		 m_items_quantity(vertex_array.m_items_quantity)
	{
		vertex_array.m_id = 0;
		vertex_array.m_items_quantity = 0;
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::add_vbo(const VertexBuffer& vertex_buffer)
	{
		bind();
		vertex_buffer.bind();

		for (const BufferItem& current_item : vertex_buffer.get_layout().get_items())
		{
			glEnableVertexAttribArray(m_items_quantity);
			glVertexAttribPointer(
				m_items_quantity,
				static_cast<GLint>(current_item.components_quantity),
				current_item.component_type,
				GL_FALSE,
				static_cast<GLsizei>(vertex_buffer.get_layout().get_stride()),
				reinterpret_cast<const void*>(current_item.offset)
			);
			m_items_quantity++;
		}
	}

	void VertexArray::set_ibo(const IndexBuffer& index_buffer)
	{
		bind();
		index_buffer.bind();
		m_indices_quantity = index_buffer.get_quantity();
	}
}