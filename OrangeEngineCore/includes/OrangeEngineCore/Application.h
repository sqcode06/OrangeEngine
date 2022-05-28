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

		Application(const Application&);
		Application(Application&&);
		Application operator=(const Application&) = delete;
		Application operator=(Application&&) = delete;

		virtual int start(unsigned int width, unsigned int height, const char* title, char** argv);
		virtual void onUpdate() {};
		virtual void onUIDraw() {};

		float camera_position[3] = { 0.f, 0.f, 1.f };
		float camera_rotation[3] = { 0.f, 0.f, 0.f };
		bool perspective_camera = false;
		Camera camera;

	private:
		std::unique_ptr<class Window> m_pWindow;

		EventDispatcher m_event_dispatcher;
		bool m_bCloseWindow = false;
	};
}