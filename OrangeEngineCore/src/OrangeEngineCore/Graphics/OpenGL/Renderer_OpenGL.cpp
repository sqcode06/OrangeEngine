#include "OrangeEngineCore/Graphics/OpenGL/Renderer_OpenGL.h"

#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	bool Renderer_OpenGL::init(GLFWwindow* ptrWindow)
	{
		glfwMakeContextCurrent(ptrWindow);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			spdlog::critical("Failed to initialize GLAD");
			return false;
		}

		spdlog::info("OpenGL context initialized:\nVendor: {0},\nRenderer: {1},\nVersion: {2}", get_vendor_str(), get_renderer_str(), get_version_str());
		return true;
	}

	void Renderer_OpenGL::draw(const VertexArray& vertexArray, int verticesQuantity)
	{
		vertexArray.bind();
		glDrawArrays(GL_TRIANGLES, 0, verticesQuantity);
	}

	void Renderer_OpenGL::draw_elements(const VertexArray& vertexArray)
	{
		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexArray.get_indices_quantity()), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer_OpenGL::set_clear_color(const float red, const float green, const float blue, const float alpha)
	{
		glClearColor(red, green, blue, alpha);
	}

	void Renderer_OpenGL::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Renderer_OpenGL::enable_depth_test(int depthFunc)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(depthFunc);
	}

	void Renderer_OpenGL::enable_stencil_test(char mask)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilMask(mask);
	}

	void Renderer_OpenGL::setup_stencil_test(int stencilFunc, int reference, char mask, int stencilFailFunc, int depthFailFunc, int depthSuccessFunc)
	{
		glStencilFunc(stencilFunc, reference, mask);
		glStencilOp(stencilFailFunc, depthFailFunc, depthSuccessFunc);
	}

	void Renderer_OpenGL::set_viewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset, const unsigned int bottomOffset)
	{
		glViewport(leftOffset, bottomOffset, width, height);
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