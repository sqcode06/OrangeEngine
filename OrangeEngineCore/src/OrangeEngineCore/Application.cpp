#include "OrangeEngineCore/Application.h"
#include "OrangeEngineCore/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{

	Application::Application()
	{
		spdlog::info("Application started. Logging session started.");
	}

	Application::~Application()
	{
		spdlog::info("Application closed. Logging session finished.");
	}

	int Application::start(unsigned int width, unsigned int height, const char* title, char** argv)
	{
		m_pWindow = std::make_unique<Window>(title, width, height);
		m_event_dispatcher.add_event_listener<EventWindowResize>(
			[](EventWindowResize& event)
			{
				spdlog::info("[EVENT] Changed size to {0}x{1}", event.width, event.height);
			});
		m_event_dispatcher.add_event_listener<EventMouseMoved>(
			[](EventMouseMoved& event)
			{
				spdlog::info("[EVENT] Cursor moved to {0}x{1}", event.x, event.y);
			});
		m_event_dispatcher.add_event_listener<EventWindowClose>(
			[&](EventWindowClose& event)
			{
				spdlog::info("[EVENT] The window is successfully closed");
				m_bCloseWindow = true;
			});
		m_pWindow->set_event_callback(
			[&](BaseEvent& event)
			{
				m_event_dispatcher.dispatch(event);
			}
		);
		while (!m_bCloseWindow)
		{
			m_pWindow->onUpdate();
			onUpdate();
		}
		m_pWindow = nullptr;

		/*GLfloat points[] = {
			0.0f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f
		};

		GLfloat colors[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};

		{
			ShaderLoader shaderLoader(argv[0]);
			auto pDefaultShader = shaderLoader.loadShader("DefaultShader", "shaders/default.vert", "shaders/default.frag");
			if (!pDefaultShader)
			{
				spdlog::error("Can't load shader: DefaultShader");
				return -1;
			}

			GLuint points_vbo = 0;
			glGenBuffers(1, &points_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

			GLuint colors_vbo = 0;
			glGenBuffers(1, &colors_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

			GLuint vao = 0;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			glClearColor(1, 1, 0, 1);
			while (!glfwWindowShouldClose(window))
			{
				glClear(GL_COLOR_BUFFER_BIT);

				pDefaultShader->use();
				glBindVertexArray(vao);
				glDrawArrays(GL_TRIANGLES, 0, 3);

				glfwSwapBuffers(window);
				glfwPollEvents();

				onUpdate();
			}
		}*/
		return 0;
	}

}