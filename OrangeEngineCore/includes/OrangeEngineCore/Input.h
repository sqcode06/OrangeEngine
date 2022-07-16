#pragma once

#include "Keys.h"

namespace OrangeEngine
{
	class Input
	{
	public:
		static bool is_key_pressed(const KeyCode keyCode);
		static void press_key(const KeyCode keyCode);
		static void release_key(const KeyCode keyCode);

	private:
		static bool s_keys_pressed[static_cast<size_t>(KeyCode::Last)];
	};
}