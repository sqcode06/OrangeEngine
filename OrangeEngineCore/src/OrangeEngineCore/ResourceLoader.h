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

		static void createLoader(std::string executablePath);
		static bool loadImage(std::string fileName, ImageData& imageData);

		static std::string getExecutablePath() { return m_executable_path; }
		
	private:
		static std::string m_executable_path;
	};
}