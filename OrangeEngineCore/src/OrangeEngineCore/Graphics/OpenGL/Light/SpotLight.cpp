#include "OrangeEngineCore/Graphics/OpenGL/Light/SpotLight.h"

#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 attenuation, GLfloat innerCutoff, GLfloat outerCutoff, LightMaterial lightMaterial)
		:m_position(position),
		 m_direction(direction),
		 m_attenuation(attenuation),
		 m_inner_cutoff(glm::cos(glm::radians(innerCutoff))),
		 m_outer_cutoff(glm::cos(glm::radians(outerCutoff))),
		 m_light_material(lightMaterial)
	{}

	void SpotLight::send_to_shader(std::unique_ptr<Shader>& shader, std::string name)
	{
		shader->set_vec3(name + ".ambient", m_light_material.ambient);
		shader->set_vec3(name + ".diffuse", m_light_material.diffuse);
		shader->set_vec3(name + ".specular", m_light_material.specular);
		shader->set_vec3(name + ".position", m_position);
		shader->set_vec3(name + ".direction", m_direction);
		shader->set_vec3(name + ".attenuation", m_attenuation);
		shader->set_float(name + ".inner_cutoff", &m_inner_cutoff);
		shader->set_float(name + ".outer_cutoff", &m_outer_cutoff);
	}
}