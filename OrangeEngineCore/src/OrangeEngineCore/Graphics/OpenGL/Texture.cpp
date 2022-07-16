#include "OrangeEngineCore/Graphics/OpenGL/Texture.h"

#include "OrangeEngineCore/ResourceLoader.h"

#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	constexpr GLenum convertTextureWrapTypeToGLenum(const TextureWrapType textureWrapType)
	{
		switch (textureWrapType)
		{
		case TextureWrapType::Repeat:
			return GL_REPEAT;
		case TextureWrapType::MirroredRepeat:
			return GL_MIRRORED_REPEAT;
		case TextureWrapType::ClampToEdge:
			return GL_CLAMP_TO_EDGE;
		case TextureWrapType::ClampToBorder:
			return GL_CLAMP_TO_BORDER;
		}
		spdlog::error("Unknown TextureWrapType, automatically set to \"Repeat\".");
		return GL_REPEAT;
	}

	constexpr GLenum convertTextureFilterTypeToGLenum(const TextureFilterType textureFilterType, const bool useMipMap)
	{
		if (!useMipMap)
		{
			switch (textureFilterType)
			{
			case TextureFilterType::Nearest:
				return GL_NEAREST;
			case TextureFilterType::Linear:
				return GL_LINEAR;
			}
		}
		else
		{
			switch (textureFilterType)
			{
			case TextureFilterType::Nearest:
				return GL_NEAREST_MIPMAP_LINEAR;
			case TextureFilterType::Linear:
				return GL_LINEAR_MIPMAP_LINEAR;
			}
		}
		spdlog::error("Unknown TextureFilterType, automatically set to \"Linear\".");
		return GL_LINEAR;
	}

	Texture::Texture(const char* fileName, TextureWrapType wrapType, TextureFilterType minFilterType, TextureFilterType magFilterType, bool useMipMap, Color* borderColor, bool hasAlpha)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, convertTextureWrapTypeToGLenum(wrapType));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, convertTextureWrapTypeToGLenum(wrapType));
		if (wrapType == TextureWrapType::ClampToBorder)
		{
			float color[4] = { borderColor->r, borderColor->g, borderColor->b, borderColor->a };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, convertTextureFilterTypeToGLenum(minFilterType, useMipMap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, convertTextureFilterTypeToGLenum(magFilterType, false));
		
		ImageData textureData;
		bool isLoaded = ResourceLoader::load_image(fileName, textureData);
		if (isLoaded)
		{
			if (hasAlpha) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.data);
			else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.data);
			if (useMipMap) glGenerateMipmap(GL_TEXTURE_2D);
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	Texture& Texture::operator=(Texture&& texture) noexcept
	{
		glDeleteTextures(1, &m_id);
		m_id = texture.m_id;
		texture.m_id = 0;
		return *this;
	}

	Texture::Texture(Texture&& texture) noexcept
	{
		m_id = texture.m_id;
		texture.m_id = 0;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}