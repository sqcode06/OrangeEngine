#include "OrangeEngineCore/Window.h"

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

		glfwSetErrorCallback([](int errorCode, const char* description)
			{
				spdlog::critical("GLFW error: {0}", description);
			});

		if (!glfwInit())
		{
			spdlog::critical("Failed to initialize GLFW.");
			return -1;
		}

		m_ptr_window = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		if (!m_ptr_window)
		{
			spdlog::critical("Failed to create GLFW window \"{0}\"", m_data.m_title);
			return -2;
		}
		
		if (!Renderer_OpenGL::init(m_ptr_window))
		{
			spdlog::critical("Failed to initialize OpenGL renderer");
			return -3;
		}

		glfwSetWindowUserPointer(m_ptr_window, &m_data);
		glfwSetWindowSizeCallback(m_ptr_window,
			[](GLFWwindow* ptrWindow, int width, int height)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(ptrWindow));
				data.m_width = width;
				data.m_height = height;
				EventWindowResize event(width, height);
				data.m_event_callback_function(event);
			}
		);
		glfwSetCursorPosCallback(m_ptr_window,
			[](GLFWwindow* ptrWindow, double x, double y)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(ptrWindow));
				EventMouseMoved event(x, y);
				data.m_event_callback_function(event);
			}
		);
		glfwSetWindowCloseCallback(m_ptr_window,
			[](GLFWwindow* ptrWindow)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(ptrWindow));
				EventWindowClose event;
				data.m_event_callback_function(event);
			}
		);
		glfwSetFramebufferSizeCallback(m_ptr_window,
			[](GLFWwindow* ptrWindow, int width, int height)
			{
				Renderer_OpenGL::set_viewport(width, height);
			}
		);

		UIModule::on_window_built(m_ptr_window);

		Renderer_OpenGL::enable_depth_test(GL_LESS);

		return 0;
	}

	int Window::shutdown()
	{
		UIModule::on_window_destroy();
		glfwDestroyWindow(m_ptr_window);
		glfwTerminate();
		return 0;
	}

	void Window::on_update()
	{
		glfwSwapBuffers(m_ptr_window);
		glfwPollEvents();
	}
}