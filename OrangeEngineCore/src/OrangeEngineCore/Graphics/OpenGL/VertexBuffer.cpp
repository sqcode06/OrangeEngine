#include "VertexBuffer.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	constexpr unsigned int convertShaderDataTypeToComponentsQuantity(const ShaderDataType dataType)
	{
		switch (dataType)
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

	constexpr GLenum convertUsageToGLEnum(const VertexBuffer::UsageType usage)
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

	constexpr size_t getShaderDataTypeSize(const ShaderDataType dataType)
	{
		switch (dataType)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
			return sizeof(GLfloat) * convertShaderDataTypeToComponentsQuantity(dataType);

		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return sizeof(GLint) * convertShaderDataTypeToComponentsQuantity(dataType);
		}
		spdlog::error("Unknown shader data type. Shader data type size has been set to \"0\" automatically.");
		return 0;
	}

	constexpr unsigned int convertShaderDataTypeToComponentType(const ShaderDataType dataType)
	{
		switch (dataType)
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

	BufferItem::BufferItem(const ShaderDataType dataType)
		: type(dataType)
		, component_type(convertShaderDataTypeToComponentType(dataType))
		, components_quantity(convertShaderDataTypeToComponentsQuantity(dataType))
		, size(getShaderDataTypeSize(dataType))
		, offset(0)
	{}

	VertexBuffer::VertexBuffer(const void* data, const size_t size, BufferLayout bufferLayout, const UsageType usage)
		: m_buffer_layout(std::move(bufferLayout))
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, convertUsageToGLEnum(usage));
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
	{
		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
		return *this;
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
		: m_id(vertexBuffer.m_id)
		, m_buffer_layout(std::move(vertexBuffer.m_buffer_layout))
	{
		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
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