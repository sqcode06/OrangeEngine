#include "OrangeEngineCore/Graphics/OpenGL/Light/PointLight.h"

#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	PointLight::PointLight(glm::vec3 position, glm::vec3 attenuation, LightMaterial lightMaterial)
		:m_position(position),
		 m_attenuation(attenuation),
		 m_light_material(lightMaterial)
	{}

	void PointLight::send_to_shader(std::unique_ptr<Shader>& shader, std::string name)
	{
		shader->set_vec3(name + ".ambient", m_light_material.ambient);
		shader->set_vec3(name + ".diffuse", m_light_material.diffuse);
		shader->set_vec3(name + ".specular", m_light_material.specular);
		shader->set_vec3(name + ".position", m_position);
		shader->set_vec3(name + ".attenuation", m_attenuation);
	}
}