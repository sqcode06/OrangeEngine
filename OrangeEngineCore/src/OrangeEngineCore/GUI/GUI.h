#pragma once

#include <vector>

namespace OrangeEngine
{
	class GUIObject
	{

	};

	class GUI
	{
	public:
		GUI();
		~GUI();

		GUI(const GUI&) = delete;
		GUI& operator=(const GUI&) = delete;
		GUI(GUI&&) = delete;
		GUI& operator=(GUI&&) = delete;

		void add_object(GUIObject obj);
		void init();

	private:
		std::vector<GUIObject> m_obj_arr;
	};
}