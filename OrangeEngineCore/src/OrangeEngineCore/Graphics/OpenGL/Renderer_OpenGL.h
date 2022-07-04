#pragma once

struct GLFWwindow;

namespace OrangeEngine
{
	class VertexArray;
	
	class Renderer_OpenGL
	{
	public:
		static bool init(GLFWwindow* ptrWindow);
		
		static void draw(const VertexArray& vertexArray, int verticesQuantity);
		static void draw_elements(const VertexArray& vertexArray);
		static void set_clear_color(const float red, const float green, const float blue, const float alpha);
		static void clear();
		static void enable_depth_test(int depthFunc);
		static void set_viewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset = 0, const unsigned int bottomOffset = 0);

		static const char* get_vendor_str();
		static const char* get_renderer_str();
		static const char* get_version_str();
	};
}