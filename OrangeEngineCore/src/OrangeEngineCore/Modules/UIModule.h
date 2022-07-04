#pragma once

struct GLFWwindow;

namespace OrangeEngine
{

	class UIModule
	{
	public:
		static void on_window_built(GLFWwindow* ptrWindow);
		static void on_window_destroy();
		static void on_ui_draw_begin();
		static void on_ui_draw_end();
	};
}