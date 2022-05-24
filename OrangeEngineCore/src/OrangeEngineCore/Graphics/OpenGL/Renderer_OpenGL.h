#pragma once

struct GLFWwindow;

namespace OrangeEngine
{
	class VertexArray;
	
	class Renderer_OpenGL
	{
	public:
		static bool init(GLFWwindow* pWindow);
		
		static void draw(const VertexArray& vertex_array, int vertices_quantity);
		static void draw_elements(const VertexArray& vertex_array);
		static void set_clear_color(const float red, const float green, const float blue, const float alpha);
		static void clear();
		static void enable_depth_test(int depth_func);
		static void set_viewport(const unsigned int width, const unsigned int height, const unsigned int left_offset = 0, const unsigned int bottom_offset = 0);

		static const char* get_vendor_str();
		static const char* get_renderer_str();
		static const char* get_version_str();
	};
}