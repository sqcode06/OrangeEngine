#pragma once

#include <string>

namespace OrangeEngine
{
	struct ImageData
	{
		int width;
		int height;
		unsigned char* data;
	};

	class ResourceLoader
	{
	public:
		ResourceLoader() = delete;
		~ResourceLoader() = delete;
		ResourceLoader(const ResourceLoader&) = delete;
		ResourceLoader& operator=(const ResourceLoader&) = delete;
		ResourceLoader& operator=(ResourceLoader&&) = delete;
		ResourceLoader(ResourceLoader&&) = delete;

		static void create_loader(std::string executablePath);
		static bool load_image(std::string fileName, ImageData& imageData);

		static std::string get_executable_path() { return s_executable_path; }
		
	private:
		static std::string s_executable_path;
	};
}