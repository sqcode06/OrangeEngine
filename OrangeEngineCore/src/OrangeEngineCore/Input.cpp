#include "OrangeEngineCore/Input.h"

namespace OrangeEngine
{
	bool Input::m_keys_pressed[static_cast<size_t>(KeyCode::Last)] = {};

	bool Input::is_key_pressed(const KeyCode keyCode)
	{
		return m_keys_pressed[static_cast<size_t>(keyCode)];
	}

	void Input::press_key(const KeyCode keyCode)
	{
		m_keys_pressed[static_cast<size_t>(keyCode)] = true;
	}

	void Input::release_key(const KeyCode keyCode)
	{
		m_keys_pressed[static_cast<size_t>(keyCode)] = false;
	}
}