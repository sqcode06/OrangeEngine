#include "IndexBuffer.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	constexpr GLenum convertUsageToGLEnum(const VertexBuffer::UsageType usage)
	{
		switch (usage)
		{
		case VertexBuffer::UsageType::Dynamic: return GL_DYNAMIC_DRAW;
		case VertexBuffer::UsageType::Static: return GL_STATIC_DRAW;
		case VertexBuffer::UsageType::Stream: return GL_STREAM_DRAW;
		}
		spdlog::error("Unknown IBO usage type. \"Stream\" type selected automatically.");
		return GL_STREAM_DRAW;
	}

	IndexBuffer::IndexBuffer(const void* data, size_t quantity, const VertexBuffer::UsageType usage)
		: m_quantity(std::move(quantity))
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, quantity * sizeof(GLuint), data, convertUsageToGLEnum(usage));
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
	{
		m_id = indexBuffer.m_id;
		m_quantity = indexBuffer.m_quantity;
		indexBuffer.m_id = 0;
		indexBuffer.m_quantity = 0;
		return *this;
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
		: m_id(indexBuffer.m_id)
		, m_quantity(std::move(indexBuffer.m_quantity))
	{
		indexBuffer.m_id = 0;
		indexBuffer.m_quantity = 0;
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}