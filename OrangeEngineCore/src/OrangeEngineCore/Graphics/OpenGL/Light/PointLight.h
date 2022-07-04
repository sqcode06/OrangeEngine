#pragma once

#include "OrangeEngineCore/Graphics/OpenGL/Light/LightMaterial.h"
#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"

#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace OrangeEngine
{
	class PointLight
	{
	public:
		PointLight(glm::vec3 position, glm::vec3 attenuation, LightMaterial lightMaterial);

		void send_to_shader(std::unique_ptr<Shader>& shader, std::string name);

		void set_position(glm::vec3 position) { m_position = position; }
		void set_attenuation(glm::vec3 attenuation) { m_attenuation = attenuation; }
		glm::vec3 get_position() const { return m_position; }
		glm::vec3 get_attenuation() const { return m_attenuation; }

	private:
		glm::vec3 m_position;
		glm::vec3 m_attenuation;
		LightMaterial m_light_material;
	};
}