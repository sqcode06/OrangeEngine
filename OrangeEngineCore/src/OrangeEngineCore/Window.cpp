#include "OrangeEngineCore/Window.h"

#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"
#include "OrangeEngineCore/Graphics/OpenGL/VertexBuffer.h"
#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace OrangeEngine
{
	static bool s_GLFW_initialized = false;

	GLfloat points[] = {
		0.0f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	   -0.5f, -0.5f, 0.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLfloat positions_and_colors[] = {
		 0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f
	};

	const char* vertex_shader =
		"#version 460\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec3 vertex_color;"
		"out vec3 color;"
		"void main() {"
		"   color = vertex_color;"
		"   gl_Position = vec4(vertex_position, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 460\n"
		"in vec3 color;"
		"out vec4 frag_color;"
		"void main() {"
		"   frag_color = vec4(color, 1.0);"
		"}";

	std::unique_ptr<Shader> p_shader;

	std::unique_ptr<VertexBuffer> p_points_vbo;
	std::unique_ptr<VertexBuffer> p_colors_vbo;
	std::unique_ptr<VertexArray> p_vao_2vbo;

	std::unique_ptr<VertexBuffer> p_positions_and_colors_vbo;
	std::unique_ptr<VertexArray> p_vao_1vbo;

	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		:m_data({ std::move(title), width, height })
	{
		int resultCode = init();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
	}

	Window::~Window()
	{
		spdlog::info("Window \"{0}\" closed.", m_data.m_title);
		shutdown();
	}

	int Window::init()
	{
		spdlog::info("Window \"{0}\" created.", m_data.m_title);
		if (!s_GLFW_initialized)
		{
			if (!glfwInit())
			{
				spdlog::critical("Failed to initialize GLFW.");
				return -1;
			}
			s_GLFW_initialized = true;
		}
		m_pWindow = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		if (!m_pWindow)
		{
			spdlog::critical("Failed to create GLFW window \"{0}\"", m_data.m_title);
			glfwTerminate();
			return -2;
		}
		glfwMakeContextCurrent(m_pWindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			spdlog::critical("Failed to initialize GLAD");
			return -3;
		}
		spdlog::info("Renderer: {0}, OpenGL version: {1}", glGetString(GL_RENDERER), glGetString(GL_VERSION));
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
				glViewport(0, 0, width, height);
			}
		);

		p_shader = std::make_unique<Shader>(vertex_shader, fragment_shader);
		if (!p_shader->isCompiled())
		{
			return false;
		}

		BufferLayout buffer_layout_1vec3
		{
			ShaderDataType::Float3
		};

		p_vao_2vbo = std::make_unique<VertexArray>();
		p_points_vbo = std::make_unique<VertexBuffer>(points, sizeof(points), buffer_layout_1vec3);
		p_colors_vbo = std::make_unique<VertexBuffer>(colors, sizeof(colors), buffer_layout_1vec3);

		p_vao_2vbo->add_buffer(*p_points_vbo);
		p_vao_2vbo->add_buffer(*p_colors_vbo);

		BufferLayout buffer_layout_2vec3
		{
			ShaderDataType::Float3,
			ShaderDataType::Float3
		};

		p_vao_1vbo = std::make_unique<VertexArray>();
		p_positions_and_colors_vbo = std::make_unique<VertexBuffer>(positions_and_colors, sizeof(positions_and_colors), buffer_layout_2vec3);

		p_vao_1vbo->add_buffer(*p_positions_and_colors_vbo);
	}

	int Window::shutdown()
	{
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
		return 0;
	}

	void Window::onUpdate()
	{
		glClearColor(m_bg_color[0], m_bg_color[1], m_bg_color[2], m_bg_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = m_data.m_width;
		io.DisplaySize.y = m_data.m_height;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Background Color");
		ImGui::ColorEdit4("Color Picker", m_bg_color);

		static bool use_2_vbo = true;
		ImGui::Checkbox("Two VBOs?", &use_2_vbo);

		if (use_2_vbo)
		{
			p_shader->bind();
			p_vao_2vbo->bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else
		{
			p_shader->bind();
			p_vao_1vbo->bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}