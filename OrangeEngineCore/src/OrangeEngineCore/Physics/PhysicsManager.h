#pragma once

#include "OrangeEngineCore/GameObject.h"

namespace OrangeEngine
{
	class PhysicsManager
	{
	public:
		PhysicsManager();
		~PhysicsManager();
		
		PhysicsManager(const PhysicsManager&) = delete;
		PhysicsManager& operator=(const PhysicsManager&) = delete;
		PhysicsManager(PhysicsManager&&) = delete;
		PhysicsManager& operator=(PhysicsManager&&) = delete;

	private:
		
	};
}