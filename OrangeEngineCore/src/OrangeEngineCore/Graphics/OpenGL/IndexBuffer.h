#pragma once

#include "VertexBuffer.h"

namespace OrangeEngine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const void* data, size_t quantity, const VertexBuffer::UsageType usage = VertexBuffer::UsageType::Static);
		~IndexBuffer();

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;
		IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

		void bind() const;
		static void unbind();
		size_t get_quantity() const { return m_quantity; }

	private:
		unsigned int m_id = 0;
		size_t m_quantity;
	};
}