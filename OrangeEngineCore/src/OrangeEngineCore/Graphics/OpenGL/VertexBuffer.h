#pragma once

#include <vector>

namespace OrangeEngine
{
	enum ShaderDataType
	{
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4
	};

	struct BufferItem
	{
		ShaderDataType type;
		uint32_t component_type;
		size_t components_quantity;
		size_t size;
		size_t offset;

		BufferItem(const ShaderDataType type);
	};

	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<BufferItem> items)
			:m_items(std::move(items))
		{
			size_t offset = 0;
			m_stride = 0;
			for (auto& item : m_items)
			{
				item.offset = offset;
				offset += item.size;
				m_stride += item.size;
			}
		}

		const std::vector<BufferItem>& get_items() const { return m_items; }
		size_t get_stride() const { return m_stride; }

	private:
		std::vector<BufferItem> m_items;
		size_t m_stride = 0;
	};

	class VertexBuffer
	{
	public:
		enum class UsageType
		{
			Static,
			Dynamic,
			Stream
		};

		VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout, const UsageType usage = VertexBuffer::UsageType::Static);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&& vertex_buffer) noexcept;
		VertexBuffer(VertexBuffer&& vertex_buffer) noexcept;

		void bind() const;
		static void unbind();

		const BufferLayout& get_layout() const { return m_buffer_layout; }

	private:
		unsigned int m_id = 0;
		BufferLayout m_buffer_layout;
	};
}