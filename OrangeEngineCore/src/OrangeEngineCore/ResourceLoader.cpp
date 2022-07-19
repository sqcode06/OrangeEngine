#include "OrangeEngineCore/ResourceLoader.h"

#include <stb_image/stb_image.h>
#include <spdlog/spdlog.h>

#include <fstream>
#include <sstream>

namespace OrangeEngine
{
	void ResourceLoader::create_loader(std::string executablePath)
	{
		std::size_t lastSlash = executablePath.find_last_of("\\");
		s_executable_path = std::move(executablePath.substr(0, lastSlash));
	}

	bool ResourceLoader::load_image(std::string fileName, ImageData& imageData)
	{
		int width, height, channels;
		std::string path = s_executable_path + "\\assets\\textures\\" + fileName;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (!data)
		{
			spdlog::error("Failed to load image: {0}", path);
			delete& imageData;
			return false;
		}
		imageData.width = width;
		imageData.height = height;
		imageData.data = data;
		return true;
	}

	bool load_file(std::string filePath, std::string& fileData)
	{
		std::ifstream data_stream;
		data_stream.open(filePath);
		if (!data_stream) return false;
		std::ostringstream string_stream;
		string_stream << data_stream.rdbuf();
		fileData = string_stream.str();
		return true;

	}

	bool ResourceLoader::load_shader_data(std::string shaderName, bool has_vertex_shader, bool has_geometry_shader, ShaderData& shaderData)
	{
		std::string path = s_executable_path + "\\assets\\shaders\\" + shaderName;
		if (has_vertex_shader)
		{
			std::string vertex_shader_data;
			if (!load_file(path + ".vs", vertex_shader_data))
			{
				spdlog::error("Failed to load a vertex shader file, {0}. The file could not be opened", path + ".vs");
				delete& shaderData;
				return false;
			}
			shaderData.vertex_shader = vertex_shader_data;
		}
		if (has_geometry_shader)
		{
			std::string geometry_shader_data;
			if (!load_file(path + ".gs", geometry_shader_data))
			{
				spdlog::error("Failed to load a geometry shader file, {0}. The file could not be opened", path + ".gs");
				delete& shaderData;
				return false;
			}
			shaderData.geometry_shader = geometry_shader_data;
		}
		std::string fragment_shader_data;
		if (!load_file(path + ".fs", fragment_shader_data))
		{
			spdlog::error("Failed to load a fragment shader file, {0}. The file could not be opened", path + ".fs");
			delete& shaderData;
			return false;
		}
		shaderData.fragment_shader = fragment_shader_data;
		return true;
	}

	std::string ResourceLoader::s_executable_path = "";
}