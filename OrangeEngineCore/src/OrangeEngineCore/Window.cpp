#include "OrangeEngineCore/Window.h"

#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"
#include "OrangeEngineCore/Graphics/OpenGL/VertexBuffer.h"
#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"
#include "OrangeEngineCore/Camera.h"

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

	GLfloat positions[] = {
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f
	};

	GLuint indices[] = {
		0, 1, 2,
		1, 2, 3,
		1, 3, 7,
		1, 5, 7,
		0, 2, 6,
		0, 4, 6,
		3, 2, 6,
		3, 0, 6,
		1, 0, 4,
		1, 5, 4,
		4, 5, 7,
		4, 6, 7
	};

	const char* vertex_shader =
		R"(
			#version 460
			layout(location = 0) in vec3 vertex_position;
			uniform mat4 model_matrix;
			uniform mat4 view_projection_matrix;
			out vec3 color;
			void main() {
			   gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
			}
		)";

	const char* fragment_shader =
		R"(
			#version 460
			uniform vec3 object_color;
			uniform vec3 light_color;
			out vec4 frag_color;
			void main() {
				frag_color = vec4(light_color * object_color, 1.0);
			}
		)";

	const char* light_vertex_shader =
		R"(
			#version 460
			layout(location = 0) in vec3 vertex_position;
			uniform mat4 model_matrix;
			uniform mat4 view_projection_matrix;
			void main() {
			   gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
			}
		)";

	const char* light_fragment_shader =
		R"(
			#version 460
			out vec4 frag_color;
			void main() {
				frag_color = vec4(1.0);
			}
		)";

	std::unique_ptr<Shader> p_object_shader;
	std::unique_ptr<Shader> p_light_shader;

	std::unique_ptr<VertexBuffer> p_positions_vbo;
	std::unique_ptr<IndexBuffer> p_ibo;
	std::unique_ptr<VertexArray> p_object_vao;
	std::unique_ptr<VertexArray> p_light_vao;

	float object_scale[3] = { 1.f, 1.f, 1.f };
	float object_rotation = 0.f;
	float object_position[3] = { 0.f, 0.f, 0.f };

	float camera_position[3] = { 0.f, 0.f, 1.f };
	float camera_rotation[3] = { 0.f, 0.f, 0.f };
	bool perspective_camera = false;
	Camera camera;

	float light_position[3] = { 0.0f, 1.0f, 3.0f };
	float light_rotation = 0.f;

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

		p_object_shader = std::make_unique<Shader>(vertex_shader, fragment_shader);
		if (!p_object_shader->isCompiled())
		{
			return false;
		}

		p_light_shader = std::make_unique<Shader>(light_vertex_shader, light_fragment_shader);

		if (!p_light_shader->isCompiled())
		{
			return false;
		}

		BufferLayout buffer_layout_vec3
		{
			ShaderDataType::Float3
		};

		p_object_vao = std::make_unique<VertexArray>();
		p_light_vao = std::make_unique<VertexArray>();
		p_positions_vbo = std::make_unique<VertexBuffer>(positions, sizeof(positions), buffer_layout_vec3);
		p_ibo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

		p_object_vao->add_vbo(*p_positions_vbo);
		p_object_vao->set_ibo(*p_ibo);

		p_light_vao->add_vbo(*p_positions_vbo);
		p_light_vao->set_ibo(*p_ibo);

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

		glm::mat4 model_matrix = glm::mat4(1.0f);
		model_matrix = glm::scale(model_matrix, glm::vec3(object_scale[0], object_scale[1], object_scale[2]));
		model_matrix = glm::rotate(model_matrix, glm::radians(object_rotation), glm::vec3(0, 0, 1));
		model_matrix = glm::translate(model_matrix, glm::vec3(object_position[0], object_position[1], object_position[2]));
		
		glm::mat4 light_model_matrix = glm::mat4(1.0f);
		light_model_matrix = glm::rotate(light_model_matrix, glm::radians(light_rotation), glm::vec3(1, 0, 0));
		light_model_matrix = glm::translate(light_model_matrix, glm::vec3(light_position[0], light_position[1], light_position[2]));
		
		camera.set_position_rotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]), glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		camera.set_projection_mode(perspective_camera ? Camera::ProjectionMode::Perspective : Camera::ProjectionMode::Orthographic);
		
		p_object_shader->bind();
		p_object_shader->setVec3("object_color", glm::vec3(1.0f, 0.3f, 0.0f));
		p_object_shader->setVec3("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
		p_object_shader->setMatrix4("model_matrix", model_matrix);
		p_object_shader->setMatrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());

		p_object_vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 8);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_object_vao->get_indices_quantity()), GL_UNSIGNED_INT, nullptr);

		p_light_shader->bind();
		p_light_shader->setMatrix4("model_matrix", light_model_matrix);
		p_light_shader->setMatrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());

		p_light_vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 8);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_light_vao->get_indices_quantity()), GL_UNSIGNED_INT, nullptr);

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = static_cast<float>(m_data.m_width);
		io.DisplaySize.y = static_cast<float>(m_data.m_height);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Options");

		ImGui::ColorEdit4("Background color picker", imgui_color_array);
		ImGui::SliderFloat3("Object scale", object_scale, 0.f, 2.f);
		ImGui::SliderFloat("Object rotation", &object_rotation, 0.f, 360.f);
		ImGui::SliderFloat3("Object position", object_position, -1.f, 1.f);

		ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f);
		ImGui::SliderFloat3("Camera rotation", camera_rotation, 0.f, 360.f);
		ImGui::Checkbox("Perspective camera", &perspective_camera);

		ImGui::SliderFloat3("Light position", light_position, -1.f, 1.f);
		ImGui::SliderFloat("Light rotation", &light_rotation, 0.f, 360.f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}