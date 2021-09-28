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
		return 0;
	}
}