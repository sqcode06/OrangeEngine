#include "VertexBuffer.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	constexpr unsigned int convert_shader_data_type_to_components_quantity(const ShaderDataType data_type)
	{
		switch (data_type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Int:
			return 1;
		case ShaderDataType::Float2:
		case ShaderDataType::Int2:
			return 2;
		case ShaderDataType::Float3:
		case ShaderDataType::Int3:
			return 3;
		case ShaderDataType::Float4:
		case ShaderDataType::Int4:
			return 4;
		}
		spdlog::error("Unknown shader data type. Quantity of components has been set to \"0\" automatically.");
		return 0;
	}

	constexpr GLenum convert_usage_to_GLenum(const VertexBuffer::UsageType usage)
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

	constexpr size_t get_shader_data_type_size(const ShaderDataType data_type)
	{
		switch (data_type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
			return sizeof(GLfloat) * convert_shader_data_type_to_components_quantity(data_type);

		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return sizeof(GLint) * convert_shader_data_type_to_components_quantity(data_type);
		}
		spdlog::error("Unknown shader data type. Shader data type size has been set to \"0\" automatically.");
		return 0;
	}

	constexpr unsigned int convert_shader_data_type_to_component_type(const ShaderDataType data_type)
	{
		switch (data_type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
			return GL_FLOAT;

		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		}
		spdlog::error("Unknown shader data type. Component type has been set to \"GL_FLOAT\" automatically.");
		return GL_FLOAT;
	}

	BufferItem::BufferItem(const ShaderDataType data_type)
		: type(data_type)
		, component_type(convert_shader_data_type_to_component_type(data_type))
		, components_quantity(convert_shader_data_type_to_components_quantity(data_type))
		, size(get_shader_data_type_size(data_type))
		, offset(0)
	{}

	VertexBuffer::VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout, const UsageType usage)
		: m_buffer_layout(std::move(buffer_layout))
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, convert_usage_to_GLenum(usage));
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
		: m_id(vertex_buffer.m_id)
		, m_buffer_layout(std::move(vertex_buffer.m_buffer_layout))
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