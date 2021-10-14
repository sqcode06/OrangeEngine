#pragma once

#include "GameObject.h"

#include <vector>

namespace OrangeEngine
{
	class World
	{
	public:
		World();
		~World();

		World& operator=(const World&) = delete;
		World(const World&) = delete;
		World& operator=(World&& world) = delete;
		World(World&& world) = delete;

		bool serialize();

	private:
		std::vector<GameObject> m_objects;
	};
}