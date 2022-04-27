#pragma once

#include "OrangeEngineCore/Graphics/OpenGL/Light/LightMaterial.h"
#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"

#include <glm/glm.hpp>

#include <memory>

namespace OrangeEngine
{
	class DirectionalLight
	{
	public:
		DirectionalLight(glm::vec2 angle, LightMaterial light_material);
		
		void send_to_shader(std::unique_ptr<Shader>& shader, const char* name, short name_length);
		void set_angle(glm::vec2 angle);

	private:
		glm::vec3 m_direction;
		LightMaterial m_light_material;
	};
}