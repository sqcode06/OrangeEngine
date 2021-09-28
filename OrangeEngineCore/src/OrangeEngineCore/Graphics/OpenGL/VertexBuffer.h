#pragma once

namespace OrangeEngine
{
	class VertexBuffer
	{
	public:
		enum class UsageType
		{
			Static,
			Dynamic,
			Stream
		};

		VertexBuffer(const void* data, const size_t size, const UsageType usage = VertexBuffer::UsageType::Static);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&& vertex_buffer) noexcept;
		VertexBuffer(VertexBuffer&& vertex_buffer) noexcept;

		void bind() const;
		static void unbind();

	private:
		unsigned int m_id = 0;
	};
}