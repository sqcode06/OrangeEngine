#include "OrangeEngineCore/ResourceLoader.h"

#include <stb_image/stb_image.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	void ResourceLoader::createLoader(std::string executablePath)
	{
		std::size_t lastSlash = executablePath.find_last_of("\\");
		m_executable_path = std::move(executablePath.substr(0, lastSlash));
	}

	bool ResourceLoader::loadImage(std::string fileName, ImageData& imageData)
	{
		int width, height, channels;
		std::string path = m_executable_path + "\\assets\\textures\\" + fileName;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (!data)
		{
			spdlog::error("Failed to load image: {0}", path);
			return false;
		}
		imageData.width = width;
		imageData.height = height;
		imageData.data = data;
		return true;
	}

	std::string ResourceLoader::m_executable_path = "";
}