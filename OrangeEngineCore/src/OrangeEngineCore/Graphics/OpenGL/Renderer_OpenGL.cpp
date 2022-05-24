#include "OrangeEngineCore/Graphics/OpenGL/Renderer_OpenGL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"

#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	bool Renderer_OpenGL::init(GLFWwindow* pWindow)
	{
		glfwMakeContextCurrent(pWindow);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			spdlog::critical("Failed to initialize GLAD");
			return false;
		}

		spdlog::info("OpenGL context initialized:\nVendor: {0},\nRenderer: {1},\nVersion: {2}", get_vendor_str(), get_renderer_str(), get_version_str());
		return true;
	}

	void Renderer_OpenGL::draw(const VertexArray& vertex_array, int vertices_quantity)
	{
		vertex_array.bind();
		glDrawArrays(GL_TRIANGLES, 0, vertices_quantity);
	}

	void Renderer_OpenGL::draw_elements(const VertexArray& vertex_array)
	{
		vertex_array.bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertex_array.get_indices_quantity()), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer_OpenGL::set_clear_color(const float red, const float green, const float blue, const float alpha)
	{
		glClearColor(red, green, blue, alpha);
	}

	void Renderer_OpenGL::clear()
	{
		glIsEnabled(GL_DEPTH_TEST) ? glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) : glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer_OpenGL::enable_depth_test(int depth_func)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(depth_func);
	}

	void Renderer_OpenGL::set_viewport(const unsigned int width, const unsigned int height, const unsigned int left_offset, const unsigned int bottom_offset)
	{
		glViewport(left_offset, bottom_offset, width, height);
	}

	const char* Renderer_OpenGL::get_vendor_str()
	{
		return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	}

	const char* Renderer_OpenGL::get_renderer_str()
	{
		return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	}

	const char* Renderer_OpenGL::get_version_str()
	{
		return reinterpret_cast<const char*>(glGetString(GL_VERSION));
	}
}