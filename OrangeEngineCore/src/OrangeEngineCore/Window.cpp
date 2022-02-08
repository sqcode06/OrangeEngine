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

#include <glm/glm.hpp>

namespace OrangeEngine
{
	static bool s_GLFW_initialized = false;

	GLfloat positions_and_colors[] = {
		-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 2, 2, 3, 0
	};

	const char* vertex_shader =
		R"(
			#version 460
			layout(location = 0) in vec3 vertex_position;
			layout(location = 1) in vec3 vertex_color;
			uniform mat4 model_matrix;
			out vec3 color;
			void main() {
			   color = vertex_color;
			   gl_Position = model_matrix * vec4(vertex_position, 1.0);
			}
		)";

	const char* fragment_shader =
		R"(
			#version 460
			in vec3 color;
			out vec4 frag_color;
			void main() {
				frag_color = vec4(color, 1.0);
			}
		)";

	std::unique_ptr<Shader> p_shader;

	std::unique_ptr<VertexBuffer> p_positions_and_colors_vbo;
	std::unique_ptr<IndexBuffer> p_ibo;
	std::unique_ptr<VertexArray> p_vao;

	float scale[3] = { 1.f, 1.f, 1.f };
	float rotate = 0.f;
	float translate[3] = { 0.f, 0.f, 0.f };

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

		BufferLayout buffer_layout_2vec3
		{
			ShaderDataType::Float3,
			ShaderDataType::Float3
		};

		p_vao = std::make_unique<VertexArray>();
		p_positions_and_colors_vbo = std::make_unique<VertexBuffer>(positions_and_colors, sizeof(positions_and_colors), buffer_layout_2vec3);
		p_ibo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

		p_vao->add_vbo(*p_positions_and_colors_vbo);
		p_vao->set_ibo(*p_ibo);

		return 0;
	}

	int Window::shutdown()
	{
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
		return 0;
	}

	void Window::onUpdate()
	{
		glClearColor(imgui_color_array[0], imgui_color_array[1], imgui_color_array[2], imgui_color_array[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		p_shader->bind();

		glm::mat4 scale_matrix(scale[0], 0, 0, 0,
			0, scale[1], 0, 0,
			0, 0, scale[2], 0,
			0, 0, 0, 1);

		float rotate_in_rads = glm::radians(rotate);
		glm::mat4 rotate_matrix(cos(rotate_in_rads), sin(rotate_in_rads), 0, 0,
			-sin(rotate_in_rads), cos(rotate_in_rads), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		glm::mat4 translate_matrix(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			translate[0], translate[1], translate[2], 1);

		glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
		//TODO add option to do these calculations on GPU for every vertex if it is much more powerful that CPU
		p_shader->setMatrix4("model_matrix", model_matrix);

		p_vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_vao->get_indices_quantity()), GL_UNSIGNED_INT, nullptr);

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = static_cast<float>(m_data.m_width);
		io.DisplaySize.y = static_cast<float>(m_data.m_height);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Background Color");
		
		ImGui::ColorEdit4("Color Picker", imgui_color_array);
		ImGui::SliderFloat3("Scale", scale, 0.f, 2.f);
		ImGui::SliderFloat("Rotation", &rotate, 0.f, 360.f);
		ImGui::SliderFloat3("Translation", translate, -1.f, 1.f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}