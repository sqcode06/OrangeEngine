#pragma once

#include "Event.h"

#include <OrangeEngineCore/Camera.h>

#include <memory>

namespace OrangeEngine
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application operator=(const Application&) = delete;
		Application operator=(Application&&) = delete;

		virtual int start(unsigned int width, unsigned int height, const char* title, char** argv);
		virtual void on_update() {};
		virtual void on_ui_draw() {};

		void show_cursor();
		void hide_cursor();

		float camera_position[3] = { 0.f, 0.f, 1.f };
		float camera_rotation[3] = { 0.f, 0.f, 0.f };
		bool perspective_camera = true;
		Camera camera{ glm::vec3(-5.f, 0.f, 0.f) };

		bool is_cursor_present = false;

	private:
		std::unique_ptr<class Window> m_ptr_window;

		EventDispatcher m_event_dispatcher;
		bool m_if_close_window = false;
	};
}