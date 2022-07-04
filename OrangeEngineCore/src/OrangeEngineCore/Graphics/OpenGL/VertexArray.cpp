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

	VertexArray& VertexArray::operator=(VertexArray&& vertexArray) noexcept
	{
		m_id = vertexArray.m_id;
		m_items_quantity = vertexArray.m_id;
		vertexArray.m_id = 0;
		vertexArray.m_items_quantity = 0;
		return *this;
	}

	VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
		: m_id(vertexArray.m_id)
		, m_items_quantity(vertexArray.m_items_quantity)
	{
		vertexArray.m_id = 0;
		vertexArray.m_items_quantity = 0;
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::add_vbo(const VertexBuffer& vertexBuffer)
	{
		bind();
		vertexBuffer.bind();

		for (const BufferItem& current_item : vertexBuffer.get_layout().get_items())
		{
			glEnableVertexAttribArray(m_items_quantity);
			glVertexAttribPointer(
				m_items_quantity,
				static_cast<GLint>(current_item.components_quantity),
				current_item.component_type,
				GL_FALSE,
				static_cast<GLsizei>(vertexBuffer.get_layout().get_stride()),
				reinterpret_cast<const void*>(current_item.offset)
			);
			m_items_quantity++;
		}
	}

	void VertexArray::set_ibo(const IndexBuffer& indexBuffer)
	{
		bind();
		indexBuffer.bind();
		m_indices_quantity = indexBuffer.get_quantity();
	}
}