#include "OrangeEngineCore/Window.h"


#include "OrangeEngineCore/Camera.h"

#include "OrangeEngineCore/Graphics/OpenGL/Renderer_OpenGL.h"

#include "OrangeEngineCore/Modules/UIModule.h"

#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>

namespace OrangeEngine
{
	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		:m_data({ std::move(title), width, height })
	{
		int resultCode = init();
	}

	Window::~Window()
	{
		spdlog::info("Window \"{0}\" closed.", m_data.m_title);
		shutdown();
	}

	int Window::init()
	{
		spdlog::info("Window \"{0}\" created.", m_data.m_title);

		glfwSetErrorCallback([](int error_code, const char* description)
			{
				spdlog::critical("GLFW error: {0}", description);
			});

		if (!glfwInit())
		{
			spdlog::critical("Failed to initialize GLFW.");
			return -1;
		}
		m_pWindow = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		if (!m_pWindow)
		{
			spdlog::critical("Failed to create GLFW window \"{0}\"", m_data.m_title);
			return -2;
		}
		
		if (!Renderer_OpenGL::init(m_pWindow))
		{
			spdlog::critical("Failed to initialize OpenGL renderer");
			return -3;
		}

		glfwSetWindowUserPointer(m_pWindow, &m_data);
		glfwSetWindowSizeCallback(m_pWindow, 
			[](GLFWwindow* pWindow, int width, int height)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
				data.m_width = width;
				data.m_height = height;
				EventWindowResize event(width, height);
				data.eventCallbackFn(event);
			}
		);
		glfwSetCursorPosCallback(m_pWindow,
			[](GLFWwindow* pWindow, double x, double y)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
				EventMouseMoved event(x, y);
				data.eventCallbackFn(event);
			}
		);
		glfwSetWindowCloseCallback(m_pWindow,
			[](GLFWwindow* pWindow)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
				EventWindowClose event;
				data.eventCallbackFn(event);
			}
		);
		glfwSetFramebufferSizeCallback(m_pWindow,
			[](GLFWwindow* pWindow, int width, int height)
			{
				Renderer_OpenGL::set_viewport(width, height);
			}
		);

		UIModule::on_window_built(m_pWindow);

		Renderer_OpenGL::enable_depth_test(GL_LESS);

		return 0;
	}

	int Window::shutdown()
	{
		UIModule::on_window_destroy();
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
		return 0;
	}

	void Window::onUpdate()
	{
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}