#pragma once

#include "OrangeEngineCore/Event.h"

#include <memory>
#include <string>
#include <functional>

struct GLFWwindow;

namespace OrangeEngine
{
	class Window
	{
	public:
		using EventCallbackFunction = std::function<void(BaseEvent&)>;

		Window(std::string title, const unsigned int width, const unsigned int height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window operator=(const Window&) = delete;
		Window operator=(Window&&) = delete;

		void on_update();

		unsigned int get_width() const { return m_data.m_width; }
		unsigned int get_height() const { return m_data.m_height; }

		void set_event_callback(const EventCallbackFunction& callback)
		{
			m_data.m_event_callback_function = callback;
		}
		
	private:
		struct WindowData
		{
			std::string m_title;
			unsigned int m_width;
			unsigned int m_height;
			EventCallbackFunction m_event_callback_function;
		};

		int init();
		int shutdown();

		GLFWwindow* m_ptr_window = nullptr;
		WindowData m_data;
	};
}