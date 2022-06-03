#pragma once

namespace OrangeEngine
{
	enum class TextureWrapType
	{
		Repeat,
		MirroredRepeat,
		ClampToEdge,
		ClampToBorder
	};

	enum class TextureFilterType
	{
		Nearest,
		Linear
	};

	struct Color
	{
		float r;
		float g;
		float b;
		float a;
	};

	class Texture
	{
	public:
		Texture(const char* fileName, TextureWrapType wrapType, TextureFilterType minFilterType, TextureFilterType magFilterType, bool useMipMap, Color* borderColor, bool hasAlpha);
		~Texture();

		void bind() const;
		static void unbind();

	private:
		unsigned int m_id = 0;
	};
}