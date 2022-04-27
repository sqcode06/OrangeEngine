#pragma once

#include <glm/glm.hpp>

namespace OrangeEngine
{
	struct LightMaterial
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}