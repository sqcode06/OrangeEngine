#include "OrangeEngineCore/Graphics/OpenGL/Light/SpotLight.h"

#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 attenuation, GLfloat inner_cutoff, GLfloat outer_cutoff, LightMaterial light_material)
		:m_position(position),
		 m_direction(direction),
		 m_attenuation(attenuation),
		 m_inner_cutoff(glm::cos(glm::radians(inner_cutoff))),
		 m_outer_cutoff(glm::cos(glm::radians(outer_cutoff))),
		 m_light_material(light_material)
	{}

	void SpotLight::send_to_shader(std::unique_ptr<Shader>& shader, const char* name, short name_length)
	{
		if (name_length > 32)
		{
			spdlog::error("Name of the spot light is too long, it must be no larger than 32 symbols.");
			return;
		}
		char buf[42];
		strcpy(buf, name);
		strcat(buf, ".ambient");
		shader->setVec3(buf, m_light_material.ambient);
		strcpy(buf, name);
		strcat(buf, ".diffuse");
		shader->setVec3(buf, m_light_material.diffuse);
		strcpy(buf, name);
		strcat(buf, ".specular");
		shader->setVec3(buf, m_light_material.specular);
		strcpy(buf, name);
		strcat(buf, ".position");
		shader->setVec3(buf, m_position);
		strcpy(buf, name);
		strcat(buf, ".direction");
		shader->setVec3(buf, m_direction);
		strcpy(buf, name);
		strcat(buf, ".attenuation");
		shader->setVec3(buf, m_attenuation);
		strcpy(buf, name);
		strcat(buf, ".inner_cutoff");
		shader->setFloat(buf, &m_inner_cutoff);
		strcpy(buf, name);
		strcat(buf, ".outer_cutoff");
		shader->setFloat(buf, &m_outer_cutoff);
	}
}