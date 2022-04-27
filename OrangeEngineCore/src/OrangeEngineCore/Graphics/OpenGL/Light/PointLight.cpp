#include "OrangeEngineCore/Graphics/OpenGL/Light/PointLight.h"

#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	PointLight::PointLight(glm::vec3 position, glm::vec3 attenuation, LightMaterial light_material)
		:m_position(position),
		 m_attenuation(attenuation),
		 m_light_material(light_material)
	{}

	void PointLight::send_to_shader(std::unique_ptr<Shader>& shader, const char* name, short name_length)
	{
		if (name_length > 32)
		{
			spdlog::error("Name of the point light is too long, it must be no larger than 32 symbols.");
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
		strcat(buf, ".attenuation");
		shader->setVec3(buf, m_attenuation);
	}
}