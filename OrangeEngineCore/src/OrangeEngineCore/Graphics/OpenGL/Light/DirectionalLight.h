#pragma once

#include "OrangeEngineCore/Graphics/OpenGL/Light/LightMaterial.h"
#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"

#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace OrangeEngine
{
	class DirectionalLight
	{
	public:
		DirectionalLight(glm::vec2 angle, LightMaterial lightMaterial);
		
		void send_to_shader(std::unique_ptr<Shader>& shader, std::string name);
		void set_angle(glm::vec2 angle);

	private:
		glm::vec3 m_direction;
		LightMaterial m_light_material;
	};
}