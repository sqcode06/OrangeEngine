#include "OrangeEngineCore/Graphics/OpenGL/FrameBuffer.h"

#include <glad/glad.h>

namespace OrangeEngine
{
	FrameBuffer::FrameBuffer(const void* data, const size_t size)
	{
		glGenFramebuffers(1, &m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_id);
	}
}