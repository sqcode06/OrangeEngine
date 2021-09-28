#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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

	void VertexArray::add_buffer(const VertexBuffer& vertex_buffer)
	{
		bind();
		vertex_buffer.bind();

		//TODO: use VBO layout
		glEnableVertexAttribArray(m_items_quantity);
		glVertexAttribPointer(m_items_quantity, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		m_items_quantity++;
	}
}