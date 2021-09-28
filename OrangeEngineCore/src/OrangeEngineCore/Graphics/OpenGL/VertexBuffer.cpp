#include "OrangeEngineCore/Graphics/OpenGL/VertexBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	constexpr GLenum usage_GL_convert(const VertexBuffer::UsageType usage)
	{
		switch (usage)
		{
			case VertexBuffer::UsageType::Dynamic: return GL_DYNAMIC_DRAW;
			case VertexBuffer::UsageType::Static: return GL_STATIC_DRAW;
			case VertexBuffer::UsageType::Stream: return GL_STREAM_DRAW;
		}
		spdlog::error("Unknown VBO usage type. \"Stream\" type selected automatically.");
		return GL_STREAM_DRAW;
	}

	VertexBuffer::VertexBuffer(const void* data, const size_t size, const UsageType usage)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage_GL_convert(usage));
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertex_buffer) noexcept
	{
		m_id = vertex_buffer.m_id;
		vertex_buffer.m_id = 0;
		return *this;
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& vertex_buffer) noexcept
	{
		m_id = vertex_buffer.m_id;
		vertex_buffer.m_id = 0;
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}