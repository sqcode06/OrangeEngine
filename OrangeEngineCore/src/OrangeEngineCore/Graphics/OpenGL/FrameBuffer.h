#pragma once

namespace OrangeEngine
{
	class FrameBuffer
	{
	public:
		FrameBuffer(const void* data, const size_t size);
		~FrameBuffer();

		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer& operator=(const FrameBuffer&) = delete;
		FrameBuffer& operator=(FrameBuffer&& vertex_buffer) noexcept;
		FrameBuffer(FrameBuffer&& vertex_buffer) noexcept;

		void bind() const;
		static void unbind();

	private:
		unsigned int m_id = 0;
	};
}