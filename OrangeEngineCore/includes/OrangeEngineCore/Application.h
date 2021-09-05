#pragma once

#include "Event.h"

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

	private:
		std::unique_ptr<class Window> m_pWindow;

		EventDispatcher m_event_dispatcher;
		bool m_bCloseWindow = false;
	};
}