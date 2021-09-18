#pragma once

#include "../OrangeEngineCore/includes/OrangeEngineCore/Event.h"

#include <string>
#include <functional>

struct GLFWwindow;

namespace OrangeEngine
{
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(BaseEvent&)>;

		Window(std::string title, const unsigned int width, const unsigned int height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window operator=(const Window&) = delete;
		Window operator=(Window&&) = delete;

		void onUpdate();

		unsigned int getWidth() const { return m_data.m_width; }
		unsigned int getHeight() const { return m_data.m_height; }

		void set_event_callback(const EventCallbackFn& callback)
		{
			m_data.eventCallbackFn = callback;
		}
		
	private:
		struct WindowData
		{
			std::string m_title;
			unsigned int m_width;
			unsigned int m_height;
			EventCallbackFn eventCallbackFn;
		};

		int init();
		int shutdown();

		GLFWwindow* m_pWindow = nullptr;
		WindowData m_data;
		float m_bg_color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	};
}