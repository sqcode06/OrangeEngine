#include "OrangeEngineCore/Graphics/OpenGL/Light/DirectionalLight.h"

#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	DirectionalLight::DirectionalLight(glm::vec2 angle, LightMaterial light_material)
	{
		glm::vec4 direction(1, 0, 0, 1);
		glm::mat4 matrix_xz;
		glm::mat4 matrix_vy;
		matrix_xz = glm::rotate(glm::mat4(1.0f), glm::radians(angle.x), glm::vec3(0, 1, 0));
		matrix_vy = glm::rotate(glm::mat4(1.0f), glm::radians(angle.y), glm::cross(glm::vec3(direction * matrix_xz), glm::vec3(0, 1, 0)));

		m_direction = glm::vec3(direction * matrix_xz * matrix_vy);
		m_light_material = light_material;
	}

	void DirectionalLight::set_angle(glm::vec2 angle)
	{
		glm::vec4 direction(1, 0, 0, 1);
		glm::mat4 matrix_xz;
		glm::mat4 matrix_vy;
		matrix_xz = glm::rotate(glm::mat4(1.0f), glm::radians(angle.x), glm::vec3(0, 1, 0));
		matrix_vy = glm::rotate(glm::mat4(1.0f), glm::radians(angle.y), glm::cross(glm::vec3(direction * matrix_xz), glm::vec3(0, 1, 0)));

		m_direction = glm::vec3(direction * matrix_xz * matrix_vy);
	}

	void DirectionalLight::send_to_shader(std::unique_ptr<Shader>& shader, const char* name, short name_length)
	{
		if (name_length > 32)
		{
			spdlog::error("Name of the directional light is too long, it must be no larger than 32 symbols.");
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
		strcat(buf, ".direction");
		shader->setVec3(buf, m_direction);
	}
}